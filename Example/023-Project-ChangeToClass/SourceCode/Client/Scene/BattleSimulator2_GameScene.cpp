// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2 ���Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "BattleSimulator2_GameScene.h"

#include "Controller\ConsoleController.h"
#include "Controller\InputController.h"
#include "Manager\SceneManager.h"
#include "Math\Random.h"

#include "BattleSimulator2_EditorScene.h"
#include "MiniGame\BattleSimulator2\GameObject\DynamicObject\MedievalKnight.h"
#include "MiniGame\BattleSimulator2\GameObject\DynamicObject\Viking.h"

namespace
{
	MedievalKnight s_dummyMedievalKnight;
	Viking s_dummyViking;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BattleSimulator2_GameSceneHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(BattleSimulator2_GameSceneHelper);

public:
	static void DrawTitle();
	static void DrawUnitStat();
	static void DrawBattleReport(const BattleSimulator2_GameScene& helperTarget);

	static std::shared_ptr<MedievalKnight> CloneMedievalKnight();
	static std::shared_ptr<Viking> CloneViking();
};

void BattleSimulator2_GameSceneHelper::DrawTitle()
{
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::LIGHT_AQUA);

	Int32 drawPosY = -1;
	PUT_STRING(12, ++drawPosY, "�����������");
	PUT_STRING(12, ++drawPosY, "<�߼���� VS ����ŷ>");
	PUT_STRING(12, ++drawPosY, "�����������");

	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::WHITE);
}

void BattleSimulator2_GameSceneHelper::DrawUnitStat()
{
	Int32 drawPosY = 3;
	PUT_STRING(0, ++drawPosY, "-------------------------------------------");
	PUT_STRING(0, ++drawPosY, "              �߼����    ����ŷ");
	PUT_STRING(0, ++drawPosY, "-------------------------------------------");
	PUT_STRING(0, ++drawPosY, "HP           : %7d   %7d", s_dummyMedievalKnight.getMaxHP(), s_dummyViking.getMaxHP());
	PUT_STRING(0, ++drawPosY, "���ݷ�       : %7d   %7d", s_dummyMedievalKnight.getAttackDamage(), s_dummyViking.getAttackDamage());
	PUT_STRING(0, ++drawPosY, "���� ������  : %7d%%  %7d%%", static_cast<Int32>(s_dummyMedievalKnight.getAttackSuccessRate() * 100.0f),
		static_cast<Int32>(s_dummyViking.getAttackSuccessRate() * 100.0f));
	PUT_STRING(0, ++drawPosY, "-------------------------------------------");
}

void BattleSimulator2_GameSceneHelper::DrawBattleReport(const BattleSimulator2_GameScene& helperTarget)
{
	Int32 remainMedievalKnightCnt = static_cast<Int32>(helperTarget.m_vecMedievalKnight.size());
	Int32 remainVikingCnt = static_cast<Int32>(helperTarget.m_vecViking.size());

	Int32 drawPosX = 50;
	Int32 drawPosY = 3;
	PUT_STRING(drawPosX, ++drawPosY, "-------------------------------------------");
	PUT_STRING(drawPosX, ++drawPosY, "              �߼����    ����ŷ");
	PUT_STRING(drawPosX, ++drawPosY, "-------------------------------------------");
	PUT_STRING(drawPosX, ++drawPosY, "��Ƴ��� �� : %7d   %7d", remainMedievalKnightCnt, remainVikingCnt);

	Int32 medievalKnightDeadCnt = MedievalKnight::GetTotalCnt() - remainMedievalKnightCnt;
	Int32 vikingDeadCnt = Viking::GetTotalCnt() - remainVikingCnt;
	PUT_STRING(drawPosX, ++drawPosY, "����� ��   : %7d   %7d", medievalKnightDeadCnt, vikingDeadCnt);

	// �߼���� �δ밡 �� ���ط�
	Int32 totalMedievalKnightAttackDamage = (s_dummyViking.getMaxHP() * vikingDeadCnt);
	if (helperTarget.m_vecViking.empty() == false)
	{
		std::shared_ptr<Viking> spViking = helperTarget.m_vecViking[0];
		totalMedievalKnightAttackDamage += (s_dummyViking.getMaxHP() - spViking->getHP());
	}

	// ����ŷ �δ밡 �� ���ط�
	Int32 totalVikingAttackDamage = (s_dummyMedievalKnight.getMaxHP() * medievalKnightDeadCnt);
	if (helperTarget.m_vecMedievalKnight.empty() == false)
	{
		std::shared_ptr<MedievalKnight> spMedievalKnight = helperTarget.m_vecMedievalKnight[0];
		totalVikingAttackDamage += (s_dummyMedievalKnight.getMaxHP() - spMedievalKnight->getHP());
	}

	PUT_STRING(drawPosX, ++drawPosY, "�� ���ط�   : %7d   %7d", totalMedievalKnightAttackDamage, totalVikingAttackDamage);
	PUT_STRING(drawPosX, ++drawPosY, "-------------------------------------------");

	// ��� ���� �̰���� ������ ����غ���~
	// "�� ���ط�"�� �������� �����Ƿ� �������� �����ҰԿ�.
	// �Ʊ��� ��Ƴ��� ����ŭ 5�� ����, ������ ����� ����ŭ 3�� ����!
	Int32 totalMedievalKnightScore = (remainMedievalKnightCnt * 5) + (vikingDeadCnt * 3);
	Int32 totalVikingScore = (remainVikingCnt * 5) + (medievalKnightDeadCnt * 3);

	PUT_STRING(drawPosX, ++drawPosY, "����        : %7d   %7d", totalMedievalKnightScore, totalVikingScore);
	PUT_STRING(drawPosX, ++drawPosY, "-------------------------------------------");

	PUT_STRING(drawPosX, ++drawPosY, "�� �¸��� �δ�� ");
	if (totalMedievalKnightScore == totalVikingScore)
	{
		PUT_STRING(drawPosX, ++drawPosY, "���׿�... ������ �����ؿ�.");
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

		PUT_STRING(drawPosX, ++drawPosY, "\"%s\" �δ�׿�~!", strWinner.c_str());
	}
}

std::shared_ptr<MedievalKnight> BattleSimulator2_GameSceneHelper::CloneMedievalKnight()
{
	return (std::make_shared<MedievalKnight>(s_dummyMedievalKnight));
}

std::shared_ptr<Viking> BattleSimulator2_GameSceneHelper::CloneViking()
{
	return (std::make_shared<Viking>(s_dummyViking));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_LOG_CATEGORY(BattleSimulator2_GameScene);

EErrorType BattleSimulator2_GameScene::OnInitialize()
{
	DEBUG_LOG_CATEGORY(BattleSimulator2_GameScene, "��Ʋ �ùķ����� ��!");
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
	std::generate(m_vecMedievalKnight.begin(), m_vecMedievalKnight.end(), &BattleSimulator2_GameSceneHelper::CloneMedievalKnight);

	// ������ ����ŷ�� ����ŭ ä���ٰԿ�.
	Viking::SetTotalCnt(30);
	m_vecViking.resize(Viking::GetTotalCnt());
	std::generate(m_vecViking.begin(), m_vecViking.end(), &BattleSimulator2_GameSceneHelper::CloneViking);

	// ���� ������ ������ �����;� ��!
	//m_spWorld = std::make_unique<BattleSimulator2World>(SizeInfo{ 40, 30 });

	return EErrorType::NONE;
}

EErrorType BattleSimulator2_GameScene::OnInput()
{
	if (InputController::I()->CheckInputState("GotoIntro", EInputMappingState::DOWN) == true)
	{
		SceneMgr::I()->CreateScene<BattleSimulator2_EditorScene>(ECreateType::NEXT);
	}

	return EErrorType::NONE;
}

EErrorType BattleSimulator2_GameScene::OnUpdate()
{
	// �߼���� �Ǵ� ����ŷ�� ������ �ƹ� ó���� ���� �����Կ�!
	if ( (m_vecMedievalKnight.empty() == true) ||
		 (m_vecViking.empty() == true) )
	{
		m_bBattleEnd = true;
		return EErrorType::NONE;
	}

	// ������ �ѹ��� ����
	std::shared_ptr<MedievalKnight> spMedievalKnight = m_vecMedievalKnight[0];
	std::shared_ptr<Viking> spViking = m_vecViking[0];

#pragma region �߼���� -> ����ŷ
	spMedievalKnight->Attack(spViking);

	if (spViking->IsDeath())
	{
		m_vecViking.erase(m_vecViking.begin());
		if (m_vecViking.empty() == true)
		{
			return EErrorType::NONE;
		}

		spViking = m_vecViking[0];
	}
#pragma endregion

#pragma region ����ŷ -> �߼����
	spViking->Attack(spMedievalKnight);

	if (spMedievalKnight->IsDeath())
	{
		m_vecMedievalKnight.erase(m_vecMedievalKnight.begin());
	}
#pragma endregion

	// ������ ���� ���ֵ��� ���� ������ �����ؾ� ������
	// ��Ʋ �ùķ����ʹ� ������ �����̴ϱ� ���� ���������� �����Կ�.

	return EErrorType::NONE;
}

EErrorType BattleSimulator2_GameScene::OnRender()
{
	//if (m_spWorld->OnRender() == EErrorType::RENDER_FAIL)
	//{
	//	return EErrorType::RENDER_FAIL;
	//}

	BattleSimulator2_GameSceneHelper::DrawTitle();
	BattleSimulator2_GameSceneHelper::DrawUnitStat();

	Int32 drawPosY = 11;
	PUT_STRING(0, ++drawPosY, "���� �߼������ �� : %d / %d", static_cast<Int32>(m_vecMedievalKnight.size()), MedievalKnight::GetTotalCnt());
	PUT_STRING(0, ++drawPosY, "���� ����ŷ�� ��   : %d / %d", static_cast<Int32>(m_vecViking.size()), Viking::GetTotalCnt());

	++drawPosY;
	PUT_STRING(0, ++drawPosY, "��������������������������������������������");
	PUT_STRING(0, ++drawPosY, "���� ������ �����ҰԿ�~!");

	if (m_bBattleEnd == false)
	{
		return EErrorType::NONE;
	}

	PUT_STRING(0, ++drawPosY, "���� ������ �������~!");
	PUT_STRING(0, ++drawPosY, "���� ����� �˾ƺ����?");
	PUT_STRING(0, ++drawPosY, "��������������������������������������������");

	BattleSimulator2_GameSceneHelper::DrawBattleReport(*this);
	return EErrorType::NONE;
}

EErrorType BattleSimulator2_GameScene::OnFinalize()
{
	return EErrorType::NONE;
}