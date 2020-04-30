// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2의 게임 결과를 보고합니다.
// 수집한 데이터를 이용해서 점수를 계산하고 이긴 팀을 알려줍니다.
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
		m_strWinnerGuide = "비겼습니다...";
	}
	else
	{
		std::string strWinner;
		if (m_arrTotalScore[0] > m_arrTotalScore[1])
		{
			strWinner = "중세기사";
		}
		else
		{
			strWinner = "바이킹";
		}

		m_strWinnerGuide = common_func::MakeFormatString("\"%s\" 부대가 이겼습니다~!", strWinner.c_str());
	}
}

void BattleSimulator2_BattleReporter::DrawUnitStat() const
{
	COORD drawPos{ 82, 0 };
	common_func::DrawBorder(drawPos, SizeInfo{ 17, 6 });

	// 유닛 스탯 출력!
	UnitPtr spMedievalKnight = BattleSimulator2_DataCollector::I()->FindPrototypeUnit(EObjID::MEDIEVAL_KNIGHT);
	UnitPtr spViking = BattleSimulator2_DataCollector::I()->FindPrototypeUnit(EObjID::VIKING);

	drawPos.X += 2;
	PUT_STRING(drawPos.X, ++drawPos.Y, "              중세기사    바이킹");

	++drawPos.Y;
	PUT_STRING(drawPos.X, ++drawPos.Y, "HP           : %7d   %7d",
		spMedievalKnight->getMaxHP(), spViking->getMaxHP());
	PUT_STRING(drawPos.X, ++drawPos.Y, "모양         : %7s   %7s",
		spMedievalKnight->getShape().c_str(), spViking->getShape().c_str());
	PUT_STRING(drawPos.X, ++drawPos.Y, "공격력       : %7d   %7d",
		spMedievalKnight->getAttackDamage(), spViking->getAttackDamage());
	PUT_STRING(drawPos.X, ++drawPos.Y, "공격 성공율  : %7d%%  %7d%%",
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

	PUT_STRING(drawPos.X + 2, ++drawPos.Y, "남은 중세기사의 수 : %d / %d", medievalKnight_totalCnt, medievalKnight_remainCnt);
	PUT_STRING(drawPos.X + 2, ++drawPos.Y, "남은 바이킹의 수   : %d / %d", viking_totalCnt, viking_remainCnt);
}

void BattleSimulator2_BattleReporter::DrawReport() const
{
#pragma region 시간 보고
	COORD drawPos{ 82, 12 };
	SizeInfo drawSize{ 17, 3 };

	common_func::DrawBorder(drawPos, drawSize);

	drawPos.X += 2;
	PUT_STRING(drawPos.X, ++drawPos.Y, "시작 시간 : %s", m_strBattleStartTime.c_str());
	PUT_STRING(drawPos.X, ++drawPos.Y, "종료 시간 : %s", m_strBattleEndTime.c_str());
	PUT_STRING(drawPos.X, ++drawPos.Y, "배틀 시간 : %d초", m_elapsedBattleTimeSecond);
#pragma endregion

#pragma region 배틀 결과 보고
	drawPos = COORD{ 82, 17 };
	drawSize = SizeInfo{ 17, 5 };

	common_func::DrawBorder(drawPos, drawSize);

	drawPos.X += 2;
	PUT_STRING(drawPos.X, ++drawPos.Y, "              중세기사    바이킹");
	
	Int32 medievalKnight_remainCnt =
		BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::MEDIEVAL_KNIGHT, EBattleDataType::REMAIN_UNIT_CNT);
	Int32 viking_remainCnt =
		BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::VIKING, EBattleDataType::REMAIN_UNIT_CNT);
	
	++drawPos.Y;
	PUT_STRING(drawPos.X, ++drawPos.Y, "살아남은 수 : %7d   %7d", medievalKnight_remainCnt, viking_remainCnt);

	Int32 medievalKnight_deathCnt = 
		BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::MEDIEVAL_KNIGHT, EBattleDataType::DEATH_UNIT_CNT);
	Int32 viking_deathCnt =
		BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::VIKING, EBattleDataType::DEATH_UNIT_CNT);
	PUT_STRING(drawPos.X, ++drawPos.Y, "사망한 수   : %7d   %7d", medievalKnight_deathCnt, viking_deathCnt);

	Int32 medievalKnight_totalAttackDamage =
		BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::MEDIEVAL_KNIGHT, EBattleDataType::TOTAL_ATTACK_DAMAGE);
	Int32 viking_totalAttackDamage = 
		BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::VIKING, EBattleDataType::TOTAL_ATTACK_DAMAGE);
	PUT_STRING(drawPos.X, ++drawPos.Y, "준 피해량   : %7d   %7d", medievalKnight_totalAttackDamage, viking_totalAttackDamage);
#pragma endregion

#pragma region 총점 보고
	drawPos = COORD{ 82, 24 };
	drawSize = SizeInfo{ 17, 4 };

	common_func::DrawBorder(drawPos, drawSize);

	// 어느 쪽이 이겼는지 점수를 계산해보죠~
	// "준 피해량"은 공정하지 않으므로 점수에서 제외할게요.
	// 아군이 살아남은 수만큼 5점 득점, 적군이 사망된 수만큼 3점 득점!
	drawPos.X += 2;
	PUT_STRING(drawPos.X, ++drawPos.Y, "중세기사의 총점 : %7d", m_arrTotalScore[0]);
	PUT_STRING(drawPos.X, ++drawPos.Y, "바이킹의 총점   : %7d", m_arrTotalScore[1]);

	++drawPos.Y;
	PUT_STRING(drawPos.X, ++drawPos.Y, m_strWinnerGuide.c_str());
#pragma endregion
}
