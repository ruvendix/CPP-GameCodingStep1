// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2�� ���� ����� �����մϴ�.
// ������ �����͸� �̿��ؼ� ������ ����ϰ� �̱� ���� �˷��ݴϴ�.
// =====================================================================================

#include "PCH.h"
#include "BattleSimulator2_BattleReporter.h"

#include "Timer\StopwatchTimer.h"
#include "Controller\ConsoleController.h"

#include "GameObject\DynamicObject\Unit.h"
#include "BattleSimulator2_DataCollector.h"

using StopwatchTimerPtr = std::shared_ptr<StopwatchTimer>;

DEFINE_PHOENIX_SINGLETON(BattleSimulator2_BattleReporter);

void BattleSimulator2_BattleReporter::Result()
{
	StopwatchTimerPtr spBattleTimer = BattleSimulator2_DataCollector::I()->getBattleTimer();
	m_strBattleStartTime = rx_time::MakeTimeString_HHMMSS(spBattleTimer->getStartTime());
	m_strBattleEndTime = rx_time::MakeTimeString_HHMMSS(spBattleTimer->getEndTime());
	rx_time::ToHHMMSS(spBattleTimer->getElaspedTime(), nullptr, nullptr, &m_elapsedBattleTimeSecond);

	Int32 medievalKnight_remainCnt =
		BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::MEDIEVAL_KNIGHT, EBattleDataType::REMAIN_UNIT_CNT);
	Int32 medievalKnight_deathCnt =
		BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::MEDIEVAL_KNIGHT, EBattleDataType::DEATH_UNIT_CNT);

	Int32 viking_remainCnt =
		BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::VIKING, EBattleDataType::REMAIN_UNIT_CNT);
	Int32 viking_deathCnt =
		BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::VIKING, EBattleDataType::DEATH_UNIT_CNT);

	Int32 medievalKnightIdx = common_func::ToUnderlyingType(EObjID::END_DYNAMIC_OBJ_ID) - common_func::ToUnderlyingType(EObjID::MEDIEVAL_KNIGHT) - 1;
	Int32 vikingIdx = common_func::ToUnderlyingType(EObjID::END_DYNAMIC_OBJ_ID) - common_func::ToUnderlyingType(EObjID::VIKING) - 1;

	m_arrTotalScore[medievalKnightIdx] = (medievalKnight_remainCnt * 5) + (viking_deathCnt * 3);
	m_arrTotalScore[vikingIdx] = (viking_remainCnt * 5) + (medievalKnight_deathCnt * 3);

	if (m_arrTotalScore[medievalKnightIdx] == m_arrTotalScore[vikingIdx])
	{
		m_strWinnerGuide = "�����ϴ�...";
	}
	else
	{
		std::string strWinner;
		if (m_arrTotalScore[0] > m_arrTotalScore[1])
		{
			strWinner = "�߼����";
		}
		else
		{
			strWinner = "����ŷ";
		}

		m_strWinnerGuide = common_func::MakeFormatString("\"%s\" �δ밡 �̰���ϴ�~!", strWinner.c_str());
	}
}

void BattleSimulator2_BattleReporter::DrawUnitStat() const
{
	COORD drawPos{ 82, 0 };
	common_func::DrawBorder(drawPos, SizeInfo{ 17, 6 });

	// ���� ���� ���!
	UnitPtr spMedievalKnight = BattleSimulator2_DataCollector::I()->FindPrototypeUnit(EObjID::MEDIEVAL_KNIGHT);
	UnitPtr spViking = BattleSimulator2_DataCollector::I()->FindPrototypeUnit(EObjID::VIKING);

	drawPos.X += 2;
	PUT_STRING(drawPos.X, ++drawPos.Y, "              �߼����    ����ŷ");

	++drawPos.Y;
	PUT_STRING(drawPos.X, ++drawPos.Y, "HP           : %7d   %7d",
		spMedievalKnight->getMaxHP(), spViking->getMaxHP());
	PUT_STRING(drawPos.X, ++drawPos.Y, "���         : %7s   %7s",
		spMedievalKnight->getShape().c_str(), spViking->getShape().c_str());
	PUT_STRING(drawPos.X, ++drawPos.Y, "���ݷ�       : %7d   %7d",
		spMedievalKnight->getAttackDamage(), spViking->getAttackDamage());
	PUT_STRING(drawPos.X, ++drawPos.Y, "���� ������  : %7d%%  %7d%%",
		static_cast<Int32>(spMedievalKnight->getAttackSuccessRate() * 100.0f),
		static_cast<Int32>(spViking->getAttackSuccessRate() * 100.0f));
}

void BattleSimulator2_BattleReporter::DrawRemainUnit() const
{
	COORD drawPos{ 82, 8 };
	SizeInfo drawSize{ 17, 2 };

	common_func::DrawBorder(drawPos, drawSize);

	Int32 medievalKnight_totalCnt = BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::MEDIEVAL_KNIGHT, EBattleDataType::TOTAL_UNIT_CNT);
	Int32 medievalKnight_remainCnt = BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::MEDIEVAL_KNIGHT, EBattleDataType::REMAIN_UNIT_CNT);

	Int32 viking_totalCnt = BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::VIKING, EBattleDataType::TOTAL_UNIT_CNT);
	Int32 viking_remainCnt = BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::VIKING, EBattleDataType::REMAIN_UNIT_CNT);

	PUT_STRING(drawPos.X + 2, ++drawPos.Y, "���� �߼������ �� : %d / %d", medievalKnight_totalCnt, medievalKnight_remainCnt);
	PUT_STRING(drawPos.X + 2, ++drawPos.Y, "���� ����ŷ�� ��   : %d / %d", viking_totalCnt, viking_remainCnt);
}

void BattleSimulator2_BattleReporter::DrawReport() const
{
#pragma region �ð� ����
	COORD drawPos{ 82, 12 };
	SizeInfo drawSize{ 17, 3 };

	common_func::DrawBorder(drawPos, drawSize);

	drawPos.X += 2;
	PUT_STRING(drawPos.X, ++drawPos.Y, "���� �ð� : %s", m_strBattleStartTime.c_str());
	PUT_STRING(drawPos.X, ++drawPos.Y, "���� �ð� : %s", m_strBattleEndTime.c_str());
	PUT_STRING(drawPos.X, ++drawPos.Y, "��Ʋ �ð� : %d��", m_elapsedBattleTimeSecond);
#pragma endregion

#pragma region ��Ʋ ��� ����
	drawPos = COORD{ 82, 17 };
	drawSize = SizeInfo{ 17, 5 };

	common_func::DrawBorder(drawPos, drawSize);

	drawPos.X += 2;
	PUT_STRING(drawPos.X, ++drawPos.Y, "              �߼����    ����ŷ");
	
	Int32 medievalKnight_remainCnt =
		BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::MEDIEVAL_KNIGHT, EBattleDataType::REMAIN_UNIT_CNT);
	Int32 viking_remainCnt =
		BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::VIKING, EBattleDataType::REMAIN_UNIT_CNT);
	
	++drawPos.Y;
	PUT_STRING(drawPos.X, ++drawPos.Y, "��Ƴ��� �� : %7d   %7d", medievalKnight_remainCnt, viking_remainCnt);

	Int32 medievalKnight_deathCnt = 
		BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::MEDIEVAL_KNIGHT, EBattleDataType::DEATH_UNIT_CNT);
	Int32 viking_deathCnt =
		BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::VIKING, EBattleDataType::DEATH_UNIT_CNT);
	PUT_STRING(drawPos.X, ++drawPos.Y, "����� ��   : %7d   %7d", medievalKnight_deathCnt, viking_deathCnt);

	Int32 medievalKnight_totalAttackDamage =
		BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::MEDIEVAL_KNIGHT, EBattleDataType::TOTAL_ATTACK_DAMAGE);
	Int32 viking_totalAttackDamage = 
		BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::VIKING, EBattleDataType::TOTAL_ATTACK_DAMAGE);
	PUT_STRING(drawPos.X, ++drawPos.Y, "�� ���ط�   : %7d   %7d", medievalKnight_totalAttackDamage, viking_totalAttackDamage);
#pragma endregion

#pragma region ���� ����
	drawPos = COORD{ 82, 24 };
	drawSize = SizeInfo{ 17, 4 };

	common_func::DrawBorder(drawPos, drawSize);

	// ��� ���� �̰���� ������ ����غ���~
	// "�� ���ط�"�� �������� �����Ƿ� �������� �����ҰԿ�.
	// �Ʊ��� ��Ƴ��� ����ŭ 5�� ����, ������ ����� ����ŭ 3�� ����!
	drawPos.X += 2;
	PUT_STRING(drawPos.X, ++drawPos.Y, "�߼������ ���� : %7d", m_arrTotalScore[0]);
	PUT_STRING(drawPos.X, ++drawPos.Y, "����ŷ�� ����   : %7d", m_arrTotalScore[1]);

	++drawPos.Y;
	PUT_STRING(drawPos.X, ++drawPos.Y, m_strWinnerGuide.c_str());
#pragma endregion
}
