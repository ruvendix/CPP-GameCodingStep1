// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2 씬입니다.
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
//	PUT_STRING(12, ++drawPosY, "▲▲▲▲▲▲▲▲▲▲");
//	PUT_STRING(12, ++drawPosY, "<중세기사 VS 바이킹>");
//	PUT_STRING(12, ++drawPosY, "▼▼▼▼▼▼▼▼▼▼");
//
//	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::WHITE);
//}
//
//void BattleSimulator2_GameSceneHelper::DrawUnitStat()
//{
//	Int32 drawPosY = 3;
//	PUT_STRING(0, ++drawPosY, "-------------------------------------------");
//	PUT_STRING(0, ++drawPosY, "              중세기사    바이킹");
//	PUT_STRING(0, ++drawPosY, "-------------------------------------------");
//	PUT_STRING(0, ++drawPosY, "HP           : %7d   %7d", s_dummyMedievalKnight.getMaxHP(), s_dummyViking.getMaxHP());
//	PUT_STRING(0, ++drawPosY, "공격력       : %7d   %7d", s_dummyMedievalKnight.getAttackDamage(), s_dummyViking.getAttackDamage());
//	PUT_STRING(0, ++drawPosY, "공격 성공율  : %7d%%  %7d%%", static_cast<Int32>(s_dummyMedievalKnight.getAttackSuccessRate() * 100.0f),
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
//	PUT_STRING(drawPosX, ++drawPosY, "              중세기사    바이킹");
//	PUT_STRING(drawPosX, ++drawPosY, "-------------------------------------------");
//	PUT_STRING(drawPosX, ++drawPosY, "살아남은 수 : %7d   %7d", remainMedievalKnightCnt, remainVikingCnt);
//
//	Int32 medievalKnightDeadCnt = MedievalKnight::GetTotalCnt() - remainMedievalKnightCnt;
//	Int32 vikingDeadCnt = Viking::GetTotalCnt() - remainVikingCnt;
//	PUT_STRING(drawPosX, ++drawPosY, "사망한 수   : %7d   %7d", medievalKnightDeadCnt, vikingDeadCnt);
//
//	// 중세기사 부대가 준 피해량
//	Int32 totalMedievalKnightAttackDamage = (s_dummyViking.getMaxHP() * vikingDeadCnt);
//	if (helperTarget.m_vecViking.empty() == false)
//	{
//		std::shared_ptr<Viking> spViking = helperTarget.m_vecViking[0];
//		totalMedievalKnightAttackDamage += (s_dummyViking.getMaxHP() - spViking->getHP());
//	}
//
//	// 바이킹 부대가 준 피해량
//	Int32 totalVikingAttackDamage = (s_dummyMedievalKnight.getMaxHP() * medievalKnightDeadCnt);
//	if (helperTarget.m_vecMedievalKnight.empty() == false)
//	{
//		std::shared_ptr<MedievalKnight> spMedievalKnight = helperTarget.m_vecMedievalKnight[0];
//		totalVikingAttackDamage += (s_dummyMedievalKnight.getMaxHP() - spMedievalKnight->getHP());
//	}
//
//	PUT_STRING(drawPosX, ++drawPosY, "준 피해량   : %7d   %7d", totalMedievalKnightAttackDamage, totalVikingAttackDamage);
//	PUT_STRING(drawPosX, ++drawPosY, "-------------------------------------------");
//
//	// 어느 쪽이 이겼는지 점수를 계산해보죠~
//	// "준 피해량"은 공정하지 않으므로 점수에서 제외할게요.
//	// 아군이 살아남은 수만큼 5점 득점, 적군이 사망된 수만큼 3점 득점!
//	Int32 totalMedievalKnightScore = (remainMedievalKnightCnt * 5) + (vikingDeadCnt * 3);
//	Int32 totalVikingScore = (remainVikingCnt * 5) + (medievalKnightDeadCnt * 3);
//
//	PUT_STRING(drawPosX, ++drawPosY, "총점        : %7d   %7d", totalMedievalKnightScore, totalVikingScore);
//	PUT_STRING(drawPosX, ++drawPosY, "-------------------------------------------");
//
//	PUT_STRING(drawPosX, ++drawPosY, "※ 승리한 부대는 ");
//	if (totalMedievalKnightScore == totalVikingScore)
//	{
//		PUT_STRING(drawPosX, ++drawPosY, "없네요... 점수가 동일해요.");
//	}
//	else
//	{
//		std::string strWinner;
//		if (totalMedievalKnightScore > totalVikingScore)
//		{
//			strWinner = "중세기사";
//		}
//		else
//		{
//			strWinner = "바이킹";
//		}
//
//		PUT_STRING(drawPosX, ++drawPosY, "\"%s\" 부대네요~!", strWinner.c_str());
//	}
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_LOG_CATEGORY(BattleSimulator2_GameScene);

EErrorType BattleSimulator2_GameScene::OnInitialize()
{
	DEBUG_LOG_CATEGORY(BattleSimulator2_GameScene, "배틀 시뮬레이터 씬!");
	InputController::I()->InsertInputMappingInfo("GotoIntro", VK_ESCAPE);

	// 월드와 레벨 디자인을 불러옵니다.
	// 이미 에디터 씬에서 불러온 상태지만 일반적인 상황에 맞추기 위해 다시 불러옵니다.
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

	// 타입, 첫번째 컨테, 두번째 컨테

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

	// 원래는 죽은 유닛들의 대한 정보도 저장해야 하지만
	// 배틀 시뮬레이터는 간단한 게임이니까 따로 저장하지는 않을게요.
	for (auto& iter : m_vecUnit)
	{
		Unit::UnitPtr spUnit = common_func::KindCastSP<Unit>(iter);
		CHECK_NULLPTR_CONTINUE(spUnit);

		if (spUnit->IsDeath())
		{
			// 렌더링에서도 제외
			continue;
		}

		// 시야 범위만큼 먼저 유닛을 리스트에 추가!
		spUnit->ClearUnitInRange();
		spUnit->FilterUnitInRange(m_vecUnit, m_spWorld->getSize());

		// 추가된 리스트에서 가장 최단 거리는?
		Unit::UnitPtr targetUnit = spUnit->SearchShortestPathEnemyInRange();
		if ( (targetUnit == nullptr) ||
			 (targetUnit->IsDeath()) )
		{
			continue; // 승리한 거 아님? 그건 아님!
		}

		// X와 Y축은 어느 방향으로 이동해야 함?
		spUnit->AdjustMoveAxisDir(targetUnit);
		
		EPreferMoveAxis preferMoveAxis = static_cast<EPreferMoveAxis>(math::RandomUtil::GenerateRandom(0, 1));
		spUnit->setPreferMoveAxis(preferMoveAxis);

		const COORD prevPos = spUnit->getPos();
		if (spUnit->MoveToTarget(targetUnit) == false)
		{
			// 공격 개시!
			spUnit->Attack(targetUnit);

			if (targetUnit->IsDeath())
			{
				// 죽으면 이펙트 남기기
				targetUnit->setShape("★"); // 시체 길막?

				std::string strTrigger = common_func::MakeFormatString("%s_%d", "Excute_DieUnit", s_triggerDieUnitID++);
				TriggerTimerMgr::I()->AddTriggerTimer(strTrigger, 0.8f, 0.0f,
					this, &BattleSimulator2_GameScene::OnTrigger_DieUnit, false, false);
			}
		}

		// 유닛의 위치가 겹치는지 확인!
		for (const auto& iter2 : m_vecUnit)
		{
			CHECK_NULLPTR_CONTINUE(iter2);

			if (iter == iter2)
			{
				continue;
			}

			// 위치가 겹치면 길을 새로 조정해야 하는데 길찾기 알고리즘이 필요하므로 생략...
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
	//PUT_STRING(0, ++drawPosY, "남은 중세기사의 수 : %d / %d", static_cast<Int32>(m_vecMedievalKnight.size()), MedievalKnight::GetTotalCnt());
	//PUT_STRING(0, ++drawPosY, "남은 바이킹의 수   : %d / %d", static_cast<Int32>(m_vecViking.size()), Viking::GetTotalCnt());

	//++drawPosY;
	//PUT_STRING(0, ++drawPosY, "∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼");
	//PUT_STRING(0, ++drawPosY, "모의 전투를 시작할게요~!");

	//if (m_bBattleEnd == false)
	//{
	//	return EErrorType::NOTHING;
	//}

	//PUT_STRING(0, ++drawPosY, "모의 전투가 끝났어요~!");
	//PUT_STRING(0, ++drawPosY, "전투 결과를 알아볼까요?");
	//PUT_STRING(0, ++drawPosY, "∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼∼");

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
			iter->setShape("　");
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

	// 배틀이 끝났는지 여기서 확인!
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
	PUT_STRING(82, 28, "배틀 끗!");
}
