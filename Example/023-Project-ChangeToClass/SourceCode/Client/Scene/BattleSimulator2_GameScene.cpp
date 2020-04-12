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
#include "Controller\FrameController.h"
#include "Manager\SceneManager.h"
#include "Manager\TriggerTimerManager.h"
#include "Math\Random.h"

#include "BattleSimulator2_EditorScene.h"
#include "MiniGame\BattleSimulator2\BattleSimulator2World.h"
#include "MiniGame\BattleSimulator2\BattleSimulator2_LevelDesign.h"
#include "MiniGame\BattleSimulator2\GameObject\DynamicObject\MedievalKnight.h"
#include "MiniGame\BattleSimulator2\GameObject\DynamicObject\Viking.h"

namespace
{
	MedievalKnight s_dummyMedievalKnight;
	Viking s_dummyViking;

	Uint32 s_triggerDieUnitID = 0;
	Uint32 s_triggerPostDieUnitID = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//class BattleSimulator2_GameSceneHelper final
//{
//	NON_COPYABLE_ONLY_PRIVATE_CLASS(BattleSimulator2_GameSceneHelper);
//
//public:
//	static void DrawTitle();
//	static void DrawUnitStat();
//	static void DrawBattleReport(const BattleSimulator2_GameScene& helperTarget);
//
//	static std::shared_ptr<MedievalKnight> CloneMedievalKnight();
//	static std::shared_ptr<Viking> CloneViking();
//};
//
//void BattleSimulator2_GameSceneHelper::DrawTitle()
//{
//	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::LIGHT_AQUA);
//
//	Int32 drawPosY = -1;
//	PUT_STRING(12, ++drawPosY, "�����������");
//	PUT_STRING(12, ++drawPosY, "<�߼���� VS ����ŷ>");
//	PUT_STRING(12, ++drawPosY, "�����������");
//
//	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::WHITE);
//}
//
//void BattleSimulator2_GameSceneHelper::DrawUnitStat()
//{
//	Int32 drawPosY = 3;
//	PUT_STRING(0, ++drawPosY, "-------------------------------------------");
//	PUT_STRING(0, ++drawPosY, "              �߼����    ����ŷ");
//	PUT_STRING(0, ++drawPosY, "-------------------------------------------");
//	PUT_STRING(0, ++drawPosY, "HP           : %7d   %7d", s_dummyMedievalKnight.getMaxHP(), s_dummyViking.getMaxHP());
//	PUT_STRING(0, ++drawPosY, "���ݷ�       : %7d   %7d", s_dummyMedievalKnight.getAttackDamage(), s_dummyViking.getAttackDamage());
//	PUT_STRING(0, ++drawPosY, "���� ������  : %7d%%  %7d%%", static_cast<Int32>(s_dummyMedievalKnight.getAttackSuccessRate() * 100.0f),
//		static_cast<Int32>(s_dummyViking.getAttackSuccessRate() * 100.0f));
//	PUT_STRING(0, ++drawPosY, "-------------------------------------------");
//}
//
//void BattleSimulator2_GameSceneHelper::DrawBattleReport(const BattleSimulator2_GameScene& helperTarget)
//{
//	Int32 remainMedievalKnightCnt = static_cast<Int32>(helperTarget.m_vecMedievalKnight.size());
//	Int32 remainVikingCnt = static_cast<Int32>(helperTarget.m_vecViking.size());
//
//	Int32 drawPosX = 50;
//	Int32 drawPosY = 3;
//	PUT_STRING(drawPosX, ++drawPosY, "-------------------------------------------");
//	PUT_STRING(drawPosX, ++drawPosY, "              �߼����    ����ŷ");
//	PUT_STRING(drawPosX, ++drawPosY, "-------------------------------------------");
//	PUT_STRING(drawPosX, ++drawPosY, "��Ƴ��� �� : %7d   %7d", remainMedievalKnightCnt, remainVikingCnt);
//
//	Int32 medievalKnightDeadCnt = MedievalKnight::GetTotalCnt() - remainMedievalKnightCnt;
//	Int32 vikingDeadCnt = Viking::GetTotalCnt() - remainVikingCnt;
//	PUT_STRING(drawPosX, ++drawPosY, "����� ��   : %7d   %7d", medievalKnightDeadCnt, vikingDeadCnt);
//
//	// �߼���� �δ밡 �� ���ط�
//	Int32 totalMedievalKnightAttackDamage = (s_dummyViking.getMaxHP() * vikingDeadCnt);
//	if (helperTarget.m_vecViking.empty() == false)
//	{
//		std::shared_ptr<Viking> spViking = helperTarget.m_vecViking[0];
//		totalMedievalKnightAttackDamage += (s_dummyViking.getMaxHP() - spViking->getHP());
//	}
//
//	// ����ŷ �δ밡 �� ���ط�
//	Int32 totalVikingAttackDamage = (s_dummyMedievalKnight.getMaxHP() * medievalKnightDeadCnt);
//	if (helperTarget.m_vecMedievalKnight.empty() == false)
//	{
//		std::shared_ptr<MedievalKnight> spMedievalKnight = helperTarget.m_vecMedievalKnight[0];
//		totalVikingAttackDamage += (s_dummyMedievalKnight.getMaxHP() - spMedievalKnight->getHP());
//	}
//
//	PUT_STRING(drawPosX, ++drawPosY, "�� ���ط�   : %7d   %7d", totalMedievalKnightAttackDamage, totalVikingAttackDamage);
//	PUT_STRING(drawPosX, ++drawPosY, "-------------------------------------------");
//
//	// ��� ���� �̰���� ������ ����غ���~
//	// "�� ���ط�"�� �������� �����Ƿ� �������� �����ҰԿ�.
//	// �Ʊ��� ��Ƴ��� ����ŭ 5�� ����, ������ ����� ����ŭ 3�� ����!
//	Int32 totalMedievalKnightScore = (remainMedievalKnightCnt * 5) + (vikingDeadCnt * 3);
//	Int32 totalVikingScore = (remainVikingCnt * 5) + (medievalKnightDeadCnt * 3);
//
//	PUT_STRING(drawPosX, ++drawPosY, "����        : %7d   %7d", totalMedievalKnightScore, totalVikingScore);
//	PUT_STRING(drawPosX, ++drawPosY, "-------------------------------------------");
//
//	PUT_STRING(drawPosX, ++drawPosY, "�� �¸��� �δ�� ");
//	if (totalMedievalKnightScore == totalVikingScore)
//	{
//		PUT_STRING(drawPosX, ++drawPosY, "���׿�... ������ �����ؿ�.");
//	}
//	else
//	{
//		std::string strWinner;
//		if (totalMedievalKnightScore > totalVikingScore)
//		{
//			strWinner = "�߼����";
//		}
//		else
//		{
//			strWinner = "����ŷ";
//		}
//
//		PUT_STRING(drawPosX, ++drawPosY, "\"%s\" �δ�׿�~!", strWinner.c_str());
//	}
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_LOG_CATEGORY(BattleSimulator2_GameScene);

EErrorType BattleSimulator2_GameScene::OnInitialize()
{
	DEBUG_LOG_CATEGORY(BattleSimulator2_GameScene, "��Ʋ �ùķ����� ��!");
	InputController::I()->InsertInputMappingInfo("GotoIntro", VK_ESCAPE);

	// ����� ���� �������� �ҷ��ɴϴ�.
	// �̹� ������ ������ �ҷ��� �������� �Ϲ����� ��Ȳ�� ���߱� ���� �ٽ� �ҷ��ɴϴ�.
	m_spWorld = std::make_shared<BattleSimulator2World>();
	if (m_spWorld->LoadFile("BattleSimulator2.world") == EErrorType::LOAD_FILE_FAIL)
	{
		return EErrorType::LOAD_FILE_FAIL;
	}

	m_spLevelDesign = std::make_shared<BattleSimulator2_LevelDesign>();
	if (m_spLevelDesign->LoadFile("BattleSimulator2.level") == EErrorType::LOAD_FILE_FAIL)
	{
		return EErrorType::LOAD_FILE_FAIL;
	}

	// Ÿ��, ù��° ����, �ι�° ����

	const LevelDesign::VecLevelDesigndObj& vecObj = m_spLevelDesign->getVecObj();
	m_vecUnit.reserve(vecObj.size());
	common_func::CopySharedPtrContainer(vecObj, m_vecUnit);

	return EErrorType::NOTHING;
}

EErrorType BattleSimulator2_GameScene::OnInput()
{
	if (InputController::I()->CheckInputState("GotoIntro", EInputMappingState::DOWN) == true)
	{
		SceneMgr::I()->CreateScene<BattleSimulator2_EditorScene>(ECreateType::NEXT);
	}

	return EErrorType::NOTHING;
}

EErrorType BattleSimulator2_GameScene::OnUpdate()
{
	if (m_bBattleEnd == true)
	{
		return EErrorType::NOTHING;
	}

	// ������ ���� ���ֵ��� ���� ������ �����ؾ� ������
	// ��Ʋ �ùķ����ʹ� ������ �����̴ϱ� ���� ���������� �����Կ�.
	for (auto& iter : m_vecUnit)
	{
		Unit::UnitPtr spUnit = common_func::KindCastSP<Unit>(iter);
		CHECK_NULLPTR_CONTINUE(spUnit);

		if (spUnit->IsDeath())
		{
			// ������������ ����
			continue;
		}

		// �þ� ������ŭ ���� ������ ����Ʈ�� �߰�!
		spUnit->ClearUnitInRange();
		spUnit->FilterUnitInRange(m_vecUnit, m_spWorld->getSize());

		// �߰��� ����Ʈ���� ���� �ִ� �Ÿ���?
		Unit::UnitPtr targetUnit = spUnit->SearchShortestPathEnemyInRange();
		if ( (targetUnit == nullptr) ||
			 (targetUnit->IsDeath()) )
		{
			continue; // �¸��� �� �ƴ�? �װ� �ƴ�!
		}

		// X�� Y���� ��� �������� �̵��ؾ� ��?
		spUnit->AdjustMoveAxisDir(targetUnit);
		
		EPreferMoveAxis preferMoveAxis = static_cast<EPreferMoveAxis>(math::RandomUtil::GenerateRandom(0, 1));
		spUnit->setPreferMoveAxis(preferMoveAxis);

		const COORD prevPos = spUnit->getPos();
		if (spUnit->MoveToTarget(targetUnit) == false)
		{
			// ���� ����!
			spUnit->Attack(targetUnit);

			if (targetUnit->IsDeath())
			{
				// ������ ����Ʈ �����
				targetUnit->setShape("��"); // ��ü �渷?

				std::string strTrigger = common_func::MakeFormatString("%s_%d", "Excute_DieUnit", s_triggerDieUnitID++);
				TriggerTimerMgr::I()->AddTriggerTimer(strTrigger, 0.8f, 0.0f,
					this, &BattleSimulator2_GameScene::OnTrigger_DieUnit, false, false);
			}
		}

		// ������ ��ġ�� ��ġ���� Ȯ��!
		for (const auto& iter2 : m_vecUnit)
		{
			CHECK_NULLPTR_CONTINUE(iter2);

			if (iter == iter2)
			{
				continue;
			}

			// ��ġ�� ��ġ�� ���� ���� �����ؾ� �ϴµ� ��ã�� �˰����� �ʿ��ϹǷ� ����...
			if (math::IsSamePos(spUnit->getPos(), iter2->getPos()))
			{
				spUnit->setPos(prevPos);
				break;
			}
		}
	}

	return EErrorType::NOTHING;
}

EErrorType BattleSimulator2_GameScene::OnRender()
{
	if (m_spWorld->OnRender() == EErrorType::RENDER_FAIL)
	{
		return EErrorType::RENDER_FAIL;
	}

	for (const auto& iter : m_vecUnit)
	{
		CHECK_NULLPTR_CONTINUE(iter);

		if (iter->OnRender() == EErrorType::RENDER_FAIL)
		{
			return EErrorType::RENDER_FAIL;
		}
	}

	//BattleSimulator2_GameSceneHelper::DrawTitle();
	//BattleSimulator2_GameSceneHelper::DrawUnitStat();

	//Int32 drawPosY = 11;
	//PUT_STRING(0, ++drawPosY, "���� �߼������ �� : %d / %d", static_cast<Int32>(m_vecMedievalKnight.size()), MedievalKnight::GetTotalCnt());
	//PUT_STRING(0, ++drawPosY, "���� ����ŷ�� ��   : %d / %d", static_cast<Int32>(m_vecViking.size()), Viking::GetTotalCnt());

	//++drawPosY;
	//PUT_STRING(0, ++drawPosY, "��������������������������������������������");
	//PUT_STRING(0, ++drawPosY, "���� ������ �����ҰԿ�~!");

	//if (m_bBattleEnd == false)
	//{
	//	return EErrorType::NOTHING;
	//}

	//PUT_STRING(0, ++drawPosY, "���� ������ �������~!");
	//PUT_STRING(0, ++drawPosY, "���� ����� �˾ƺ����?");
	//PUT_STRING(0, ++drawPosY, "��������������������������������������������");

	//BattleSimulator2_GameSceneHelper::DrawBattleReport(*this);
	return EErrorType::NOTHING;
}

EErrorType BattleSimulator2_GameScene::OnFinalize()
{
	for (auto& iter : m_vecUnit)
	{
		CHECK_NULLPTR_CONTINUE(iter);

		if (iter->OnFinalize() == EErrorType::FINAL_FAIL)
		{
			return EErrorType::FINAL_FAIL;
		}
	}

	s_triggerDieUnitID = 0;
	s_triggerPostDieUnitID = 0;

	return EErrorType::NOTHING;
}

void BattleSimulator2_GameScene::OnTrigger_DieUnit()
{
	if (m_vecUnit.empty() == true)
	{
		return;
	}

	for (auto& iter : m_vecUnit)
	{
		CHECK_NULLPTR_CONTINUE(iter);

		if (iter->IsDeath())
		{
			iter->setShape("��");
		}
	}

	std::string strTrigger = common_func::MakeFormatString("%s_%d", "Excute_PostDieUnit", s_triggerPostDieUnitID++);
	TriggerTimerMgr::I()->AddTriggerTimer(strTrigger, 0.9f, 0.0f,
		this, &BattleSimulator2_GameScene::OnTrigger_PostDieUnit, false, false);
}

void BattleSimulator2_GameScene::OnTrigger_PostDieUnit()
{
	if (m_vecUnit.empty() == true)
	{
		return;
	}

	for (auto iter = m_vecUnit.cbegin(); iter < m_vecUnit.cend(); )
	{
		Unit::UnitPtr spUnit = *iter;
		CHECK_NULLPTR_CONTINUE(spUnit);

		if (spUnit->IsDeath())
		{
			spUnit->ClearUnitInRange();
			iter = m_vecUnit.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	// ��Ʋ�� �������� ���⼭ Ȯ��!
	Int32 vikingDeathCnt = 0;
	Int32 medievalKnightDeathCnt = 0;
	for (const auto& iter : m_vecUnit)
	{
		CHECK_NULLPTR_CONTINUE(iter);

		if (iter->getID() == common_func::ToUnderlyingType(EDynamicObjID::MEDIEVAL_KNIGHT))
		{
			++medievalKnightDeathCnt;
		}
		else if (iter->getID() == common_func::ToUnderlyingType(EDynamicObjID::VIKING))
		{
			++vikingDeathCnt;
		}
	}

	if ( (medievalKnightDeathCnt == 0) ||
		 (vikingDeathCnt == 0) )
	{
		m_bBattleEnd = true;
		RESERVE_RENDERING_STRING(3.0f, std::bind(&BattleSimulator2_GameScene::OnTrigger_BattleEnd, this));
	}
}

void BattleSimulator2_GameScene::OnTrigger_BattleEnd() const
{
	PUT_STRING(82, 28, "��Ʋ ��!");
}
