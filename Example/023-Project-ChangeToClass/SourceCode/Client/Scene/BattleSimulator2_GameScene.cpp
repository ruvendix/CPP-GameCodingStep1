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
#include "MiniGame\BattleSimulator2\BattleSimulator2_DataCollector.h"
#include "MiniGame\BattleSimulator2\BattleSimulator2_BattleReporter.h"
#include "MiniGame\BattleSimulator2\BattleSimulator2World.h"
#include "MiniGame\BattleSimulator2\BattleSimulator2_LevelDesign.h"
#include "MiniGame\BattleSimulator2\GameObject\DynamicObject\MedievalKnight.h"
#include "MiniGame\BattleSimulator2\GameObject\DynamicObject\Viking.h"

namespace
{
	Uint32 s_triggerTimerID_deathUnit = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PredUnit
{
public:
	PredUnit(UnitPtr spUnit)
		: m_spUnit(spUnit)
	{

	}

	~PredUnit() = default;

	bool operator()(UnitPtr spUnit)
	{
		if (spUnit == nullptr)
		{
			return false;
		}

		CHECK_NULLPTR(spUnit);
		return (m_spUnit == spUnit);
	}

private:
	UnitPtr m_spUnit = nullptr;
};

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

	// 월드를 불러왔으면 데이터 콜렉터를 초기화해야 해요.
	BattleSimulator2_DataCollector::I()->Initialize();

	m_spLevelDesign = std::make_shared<BattleSimulator2_LevelDesign>();
	if (m_spLevelDesign->LoadFile("BattleSimulator2.level") == EErrorType::LOAD_FILE_FAIL)
	{
		return EErrorType::LOAD_FILE_FAIL;
	}

	// 게임 씬에서는 남은 유닛수를 초기화해야 해요!
	Int32 vikingCnt = BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::VIKING, EBattleDataType::TOTAL_UNIT_CNT);
	BattleSimulator2_DataCollector::I()->ModifyBattleData(EObjID::VIKING, EBattleDataType::REMAIN_UNIT_CNT, vikingCnt);

	Int32 medievalKnightCnt = BattleSimulator2_DataCollector::I()->FindBattleData(EObjID::MEDIEVAL_KNIGHT, EBattleDataType::TOTAL_UNIT_CNT);
	BattleSimulator2_DataCollector::I()->ModifyBattleData(EObjID::MEDIEVAL_KNIGHT, EBattleDataType::REMAIN_UNIT_CNT, medievalKnightCnt);

	const VecLevelDesigndObj& vecObj = m_spLevelDesign->getVecObj();
	m_vecUnit.reserve(vecObj.size());
	common_func::CopySharedPtrContainer(vecObj, m_vecUnit);

	m_mapUnitStateCallback.Subscribe(EUnitState::IDLE,
		std::bind(&BattleSimulator2_GameScene::OnCallback_UpdateIdleState, this, std::placeholders::_1));
	m_mapUnitStateCallback.Subscribe(EUnitState::MOVE,
		std::bind(&BattleSimulator2_GameScene::OnCallback_UpdateMoveState, this, std::placeholders::_1));
	m_mapUnitStateCallback.Subscribe(EUnitState::ATTACK,
		std::bind(&BattleSimulator2_GameScene::OnCallback_UpdateAttackState, this, std::placeholders::_1));
	m_mapUnitStateCallback.Subscribe(EUnitState::DEATH,
		std::bind(&BattleSimulator2_GameScene::OnCallback_UpdateDeathState, this, std::placeholders::_1));

	BattleSimulator2_DataCollector::I()->StartBattleTime();
	return EErrorType::NOTHING;
}

EErrorType BattleSimulator2_GameScene::OnInput()
{
	if (InputController::I()->CheckInputState("GotoIntro", EInputMappingState::DOWN) == true)
	{
		BattleSimulator2_DataCollector::I()->Finalize();
		SceneMgr::I()->CreateScene<BattleSimulator2_EditorScene>(ECreateType::NEXT);
	}

	return EErrorType::NOTHING;
}

EErrorType BattleSimulator2_GameScene::OnUpdate()
{
	if (m_bGameEnd == true)
	{
		return EErrorType::NOTHING;
	}

	// 원래는 죽은 유닛들의 대한 정보도 저장해야 하지만
	// 배틀 시뮬레이터는 간단한 게임이니까 따로 저장하지는 않을게요.
	for (auto& iter : m_vecUnit)
	{
		UnitPtr spUnit = common_func::KindCastSP<Unit>(iter);
		CHECK_NULLPTR_CONTINUE(spUnit);

		MapUnitStateCallback::ElemType pCallback = m_mapUnitStateCallback.Find(spUnit->getState());
		if (pCallback != nullptr)
		{
			pCallback(spUnit);
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

	BattleSimulator2_BattleReporter::I()->DrawUnitStat();
	BattleSimulator2_BattleReporter::I()->DrawRemainUnit();

	if (m_bGameEnd == true)
	{
		BattleSimulator2_BattleReporter::I()->DrawReport();
	}

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

	s_triggerTimerID_deathUnit = 0;
	return EErrorType::NOTHING;
}

void BattleSimulator2_GameScene::OnCallback_UpdateIdleState(UnitPtr spUnit)
{
	// 시야 범위만큼 먼저 유닛을 리스트에 추가!
	spUnit->ClearUnitInRange();
	spUnit->FilterUnitInRange(m_vecUnit, m_spWorld->getSize());

	// 추가된 리스트에서 가장 최단 거리는?
	SizeInfo distance{ 0, 0 };
	UnitPtr spTargetUnit = spUnit->SearchShortestPathEnemyInRange(distance);
	if (spTargetUnit == nullptr)
	{
		return; // 시야 안에 이동할 타겟이 없음
	}

	// 적 유닛이 1칸 기준 상하좌우에 있는 경우
	if (distance.width + distance.height == 1)
	{
		spUnit->ChangeLockOnTargetUnit(spTargetUnit);
		spUnit->setState(EUnitState::ATTACK);
		//DEBUG_LOG("둘의 차이는 한칸!");
	}
	else
	{
		spUnit->setState(EUnitState::MOVE);
	}
}

void BattleSimulator2_GameScene::OnCallback_UpdateMoveState(UnitPtr spUnit)
{
	// 시야 범위만큼 먼저 유닛을 리스트에 추가!
	spUnit->ClearUnitInRange();
	spUnit->FilterUnitInRange(m_vecUnit, m_spWorld->getSize());

	// 추가된 리스트에서 가장 최단 거리는?
	SizeInfo distance{ 0, 0 };
	UnitPtr spTargetUnit = spUnit->SearchShortestPathEnemyInRange(distance);
	if (spTargetUnit == nullptr)
	{
		spUnit->setState(EUnitState::IDLE);
		return; // 시야 안에 이동할 타겟이 없음
	}

	// 적 유닛이 1칸 기준 상하좌우에 있는 경우
	if (distance.width + distance.height == 1)
	{
		spUnit->ChangeLockOnTargetUnit(spTargetUnit);
		spUnit->setState(EUnitState::ATTACK);
		//DEBUG_LOG("둘의 차이는 한칸!");
	}

	// X와 Y축은 어느 방향으로 이동해야 함?
	spUnit->AdjustMoveAxisDir(spTargetUnit);

	EPreferMoveAxis preferMoveAxis = static_cast<EPreferMoveAxis>(rx_math::Random::GenerateRandom(0, 1));
	spUnit->setPreferMoveAxis(preferMoveAxis);

	const COORD prevPos = spUnit->getPos();
	spUnit->MoveToTarget(spTargetUnit);

	// 유닛의 위치가 겹치는지 확인!
	for (const auto& iter : spUnit->getListUnitInRange())
	{
		CHECK_NULLPTR_CONTINUE(iter);

		// 위치가 겹치면 길을 새로 조정해야 하는데 길찾기 알고리즘이 필요하므로 생략...
		if (rx_math::IsSamePos(spUnit->getPos(), iter->getPos()))
		{
			spUnit->setPos(prevPos);
			break;
		}
	}
}

void BattleSimulator2_GameScene::OnCallback_UpdateAttackState(UnitPtr spUnit)
{
	UnitPtr spLockOnTargetUnit = spUnit->getLockOnTargetUnit();
	if (spLockOnTargetUnit == nullptr)
	{
		spUnit->setState(EUnitState::IDLE);
		return;
	}

	// 공격 개시!
	spUnit->Attack(spLockOnTargetUnit);

	if ( (spLockOnTargetUnit->getHP() < 0) &&
		 (spLockOnTargetUnit->IsSameState(EUnitState::ERASE) == false) ) // 제거 예정은 상태 유지!
	{
		spUnit->setState(EUnitState::IDLE);
		spUnit->ChangeLockOnTargetUnit(nullptr); // 옵저버로 nullptr 만들면 딱임

		spLockOnTargetUnit->setState(EUnitState::DEATH);
	}
}

void BattleSimulator2_GameScene::OnCallback_UpdateDeathState(UnitPtr spUnit)
{
	// 죽으면 이펙트 남기기
	spUnit->setShape("★");

	std::string strTrigger = common_func::MakeFormatString("%s_%d", "Trigger_DeathUnit", s_triggerTimerID_deathUnit++);
	TriggerTimerMgr::I()->AddTriggerTimer(strTrigger, 1.2f, 0.0f,
		this, &BattleSimulator2_GameScene::OnTrigger_DeathUnit, false, false);

	spUnit->setState(EUnitState::ERASE);

	// 죽은 유닛은 큐에 넣고 트리거 타이머가 발동될 때 front로 가져와서 제거할게요!
	m_queueDeathUnit.push(spUnit);
	//DEBUG_LOG("(%s) 유닛 넣었다!", spUnit->getNameTag().c_str());
}

void BattleSimulator2_GameScene::OnTrigger_DeathUnit()
{
	if (m_vecUnit.empty() == true)
	{
		return;
	}

	// 트리거에 등록된 순서대로 지워야 함!
	const auto& iter = std::find_if(m_vecUnit.cbegin(), m_vecUnit.cend(), PredUnit(m_queueDeathUnit.front()));
	if (iter == m_vecUnit.cend())
	{
		return;
	}

	UnitPtr spUnit = *iter;
	CHECK_NULLPTR(spUnit);

	spUnit->ChangeLockOnTargetUnit(nullptr);
	spUnit->ClearUnitInRange();

	BattleSimulator2_DataCollector::I()->ModifyBattleData(static_cast<EObjID>(spUnit->getID()),
		EBattleDataType::REMAIN_UNIT_CNT, EDataProgressDir::NEGATIVENESS, 1);

	BattleSimulator2_DataCollector::I()->ModifyBattleData(static_cast<EObjID>(spUnit->getID()),
		EBattleDataType::DEATH_UNIT_CNT, EDataProgressDir::POSITIVENESS, 1);

	//DEBUG_LOG("(%s) 유닛 제거!", spUnit->getNameTag().c_str());
	m_vecUnit.erase(iter);
	m_queueDeathUnit.pop();

	// 배틀이 끝났는지 여기서 확인!
	if ( (BattleSimulator2_DataCollector::I()->IsBattleEnd()) && 
		 (m_bGameEnd == false) )
	{
		RESERVE_RENDERING_STRING(3.0f, std::bind(&BattleSimulator2_GameScene::OnTrigger_BattleEnd, this));
	}
}

void BattleSimulator2_GameScene::OnTrigger_BattleEnd()
{
	//PUT_STRING(82, 28, "배틀 끗!");

	if (m_bGameEnd == false)
	{		
		BattleSimulator2_DataCollector::I()->EndBattleTime();
		BattleSimulator2_BattleReporter::I()->Result();

		m_bGameEnd = true;
	}
}