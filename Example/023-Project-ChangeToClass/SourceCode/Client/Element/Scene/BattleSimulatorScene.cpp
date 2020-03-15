// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ����� ���Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "BattleSimulatorScene.h"

#include "Controller\ConsoleController.h"
#include "Controller\InputController.h"
#include "Manager\SceneManager.h"
#include "IntroMenuScene.h"
#include "Math\Random.h"
#include "MiniGame\BattleSimulator\MedievalKnight.h"
#include "MiniGame\BattleSimulator\Viking.h"

namespace
{
	MedievalKnight s_dummyMedievalKnight;
	Viking s_dummyViking;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BattleSimulatorSceneHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(BattleSimulatorSceneHelper);

public:
	static void DrawTitle();
	static void DrawUnitStat();
	static void DrawBattleReport(const BattleSimulatorScene& helperTarget);

	static MedievalKnight* CloneMedievalKnight();
	static Viking* CloneViking();
};

void BattleSimulatorSceneHelper::DrawTitle()
{
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::LIGHT_AQUA);

	Int32 drawPosY = -1;
	PRINTF(12, ++drawPosY, "�����������");
	PRINTF(12, ++drawPosY, "<�߼���� VS ����ŷ>");
	PRINTF(12, ++drawPosY, "�����������");

	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::WHITE);
}

void BattleSimulatorSceneHelper::DrawUnitStat()
{
	Int32 drawPosY = 3;
	PRINTF(0, ++drawPosY, "-------------------------------------------");
	PRINTF(0, ++drawPosY, "              �߼����    ����ŷ");
	PRINTF(0, ++drawPosY, "-------------------------------------------");
	PRINTF(0, ++drawPosY, "HP           : %7d   %7d", s_dummyMedievalKnight.getMaxHP(), s_dummyViking.getMaxHP());
	PRINTF(0, ++drawPosY, "���ݷ�       : %7d   %7d", s_dummyMedievalKnight.getAttackDamage(), s_dummyViking.getAttackDamage());
	PRINTF(0, ++drawPosY, "���� ������  : %7d%%  %7d%%", static_cast<Int32>(s_dummyMedievalKnight.getAttackSuccessRate() * 100.0f),
		static_cast<Int32>(s_dummyViking.getAttackSuccessRate() * 100.0f));
	PRINTF(0, ++drawPosY, "-------------------------------------------");
}

void BattleSimulatorSceneHelper::DrawBattleReport(const BattleSimulatorScene& helperTarget)
{
	Int32 remainMedievalKnightCnt = static_cast<Int32>(helperTarget.m_vecMedievalKnight.size());
	Int32 remainVikingCnt = static_cast<Int32>(helperTarget.m_vecViking.size());

	Int32 drawPosX = 50;
	Int32 drawPosY = 3;
	PRINTF(drawPosX, ++drawPosY, "-------------------------------------------");
	PRINTF(drawPosX, ++drawPosY, "              �߼����    ����ŷ");
	PRINTF(drawPosX, ++drawPosY, "-------------------------------------------");
	PRINTF(drawPosX, ++drawPosY, "��Ƴ��� �� : %7d   %7d", remainMedievalKnightCnt, remainVikingCnt);

	Int32 medievalKnightDeadCnt = MedievalKnight::GetTotalCnt() - remainMedievalKnightCnt;
	Int32 vikingDeadCnt = Viking::GetTotalCnt() - remainVikingCnt;
	PRINTF(drawPosX, ++drawPosY, "����� ��   : %7d   %7d", medievalKnightDeadCnt, vikingDeadCnt);

	// �߼���� �δ밡 �� ���ط�
	Int32 totalMedievalKnightAttackDamage = (s_dummyViking.getMaxHP() * vikingDeadCnt);
	if (helperTarget.m_vecViking.empty() == false)
	{
		Viking* pViking = helperTarget.m_vecViking[0];
		CHECK_NULLPTR_RETURN_VOID(pViking);
		totalMedievalKnightAttackDamage += (s_dummyViking.getMaxHP() - pViking->getHP());
	}

	// ����ŷ �δ밡 �� ���ط�
	Int32 totalVikingAttackDamage = (s_dummyMedievalKnight.getMaxHP() * medievalKnightDeadCnt);
	if (helperTarget.m_vecMedievalKnight.empty() == false)
	{
		MedievalKnight* pMedievalKnight = helperTarget.m_vecMedievalKnight[0];
		CHECK_NULLPTR_RETURN_VOID(pMedievalKnight);
		totalVikingAttackDamage += (s_dummyMedievalKnight.getMaxHP() - pMedievalKnight->getHP());
	}

	PRINTF(drawPosX, ++drawPosY, "�� ���ط�   : %7d   %7d", totalMedievalKnightAttackDamage, totalVikingAttackDamage);
	PRINTF(drawPosX, ++drawPosY, "-------------------------------------------");

	// ��� ���� �̰���� ������ ����غ���~
	// "�� ���ط�"�� �������� �����Ƿ� �������� �����ҰԿ�.
	// �Ʊ��� ��Ƴ��� ����ŭ 5�� ����, ������ ����� ����ŭ 3�� ����!
	Int32 totalMedievalKnightScore = (remainMedievalKnightCnt * 5) + (vikingDeadCnt * 3);
	Int32 totalVikingScore = (remainVikingCnt * 5) + (medievalKnightDeadCnt * 3);

	PRINTF(drawPosX, ++drawPosY, "����        : %7d   %7d", totalMedievalKnightScore, totalVikingScore);
	PRINTF(drawPosX, ++drawPosY, "-------------------------------------------");

	PRINTF(drawPosX, ++drawPosY, "�� �¸��� �δ�� ");
	if (totalMedievalKnightScore == totalVikingScore)
	{
		PRINTF(drawPosX, ++drawPosY, "���׿�... ������ �����ؿ�.");
	}
	else
	{
		std::string strWinner;
		if (totalMedievalKnightScore > totalVikingScore)
		{
			strWinner = "�߼����";
		}
		else
		{
			strWinner = "����ŷ";
		}

		PRINTF(drawPosX, ++drawPosY, "\"%s\" �δ�׿�~!", strWinner.c_str());
	}
}

MedievalKnight* BattleSimulatorSceneHelper::CloneMedievalKnight()
{
	MedievalKnight* pUnit = trace_new MedievalKnight;
	*pUnit = s_dummyMedievalKnight;
	return pUnit;
}

Viking* BattleSimulatorSceneHelper::CloneViking()
{
	Viking* pUnit = trace_new Viking;
	*pUnit = s_dummyViking;
	return pUnit;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_LOG_CATEGORY(BattleSimulatorScene);

EErrorType BattleSimulatorScene::OnInitialize()
{
	DEBUG_LOG("��Ʋ �ùķ����� ��!");
	InputController::I()->InsertInputMappingInfo("GotoIntro", VK_ESCAPE);

	// ���� �߼������ ������ ���ҰԿ�.
	s_dummyMedievalKnight.setHP(180);
	s_dummyMedievalKnight.setMaxHP(180);
	s_dummyMedievalKnight.setAttackDamage(14);
	s_dummyMedievalKnight.setAttackSuccessRate(0.78f);

	// ���� ����ŷ�� ������ ���ҰԿ�.
	s_dummyViking.setHP(198);
	s_dummyViking.setMaxHP(198);
	s_dummyViking.setAttackDamage(18);
	s_dummyViking.setAttackSuccessRate(0.58f);

	// ���� ���۸��� �ܼ� Win32API�� ��� ���̹Ƿ� scanf()�� ����� �� �����.
	// ���� ���� �Է��� �޴� ����� �����ҰԿ�.

	// ������ �߼������ ����ŭ ä���ٰԿ�.
	MedievalKnight::SetTotalCnt(30);
	m_vecMedievalKnight.resize(MedievalKnight::GetTotalCnt());
	std::generate(m_vecMedievalKnight.begin(), m_vecMedievalKnight.end(), &BattleSimulatorSceneHelper::CloneMedievalKnight);

	// ������ ����ŷ�� ����ŭ ä���ٰԿ�.
	Viking::SetTotalCnt(30);
	m_vecViking.resize(Viking::GetTotalCnt());
	std::generate(m_vecViking.begin(), m_vecViking.end(), &BattleSimulatorSceneHelper::CloneViking);

	return EErrorType::NONE;
}

EErrorType BattleSimulatorScene::OnUpdate()
{
	if (InputController::I()->CheckInputState("GotoIntro", EInputMappingState::DOWN) == true)
	{
		SceneMgr::I()->CreateScene<IntroMenuScene>(ESceneType::NEXT);
	}

	// �߼���� �Ǵ� ����ŷ�� ������ �ƹ� ó���� ���� �����Կ�!
	if ( (m_vecMedievalKnight.empty() == true) ||
		 (m_vecViking.empty() == true) )
	{
		m_bBattleEnd = true;
		return EErrorType::NONE;
	}

	// ������ �ѹ��� ����
	Unit* pMedievalKnight = m_vecMedievalKnight[0];
	CHECK_NULLPTR_RETURN_ERRORTYPE(pMedievalKnight);

	Unit* pViking = m_vecViking[0];
	CHECK_NULLPTR_RETURN_ERRORTYPE(pViking);

#pragma region �߼���� -> ����ŷ
	pMedievalKnight->Attack(pViking);

	if (pViking->IsDeath())
	{
		SAFE_DELETE(pViking);
		m_vecViking.erase(m_vecViking.begin());
		if (m_vecViking.empty() == true)
		{
			return EErrorType::NONE;
		}

		pViking = m_vecViking[0];
		CHECK_NULLPTR_RETURN_ERRORTYPE(pViking);
	}
#pragma endregion

#pragma region ����ŷ -> �߼����
	pViking->Attack(pMedievalKnight);

	if (pMedievalKnight->IsDeath())
	{
		SAFE_DELETE(pMedievalKnight);
		m_vecMedievalKnight.erase(m_vecMedievalKnight.begin());
	}
#pragma endregion

	// ������ ���� ���ֵ��� ���� ������ �����ؾ� ������
	// ��Ʋ �ùķ����ʹ� ������ �����̴ϱ� ���� ���������� �����Կ�.

	return EErrorType::NONE;
}

EErrorType BattleSimulatorScene::OnRender()
{
	BattleSimulatorSceneHelper::DrawTitle();
	BattleSimulatorSceneHelper::DrawUnitStat();

	Int32 drawPosY = 11;
	PRINTF(0, ++drawPosY, "���� �߼������ �� : %d / %d", static_cast<Int32>(m_vecMedievalKnight.size()), MedievalKnight::GetTotalCnt());
	PRINTF(0, ++drawPosY, "���� ����ŷ�� ��   : %d / %d", static_cast<Int32>(m_vecViking.size()), Viking::GetTotalCnt());

	++drawPosY;
	PRINTF(0, ++drawPosY, "��������������������������������������������");
	PRINTF(0, ++drawPosY, "���� ������ �����ҰԿ�~!");

	if (m_bBattleEnd == false)
	{
		return EErrorType::NONE;
	}

	PRINTF(0, ++drawPosY, "���� ������ �������~!");
	PRINTF(0, ++drawPosY, "���� ����� �˾ƺ����?");
	PRINTF(0, ++drawPosY, "��������������������������������������������");

	BattleSimulatorSceneHelper::DrawBattleReport(*this);

	return EErrorType::NONE;
}

EErrorType BattleSimulatorScene::OnFinalize()
{
	for (auto& iter : m_vecMedievalKnight)
	{
		SAFE_DELETE(iter);
	}

	for (auto& iter : m_vecViking)
	{
		SAFE_DELETE(iter);
	}

	return EErrorType::NONE;
}
