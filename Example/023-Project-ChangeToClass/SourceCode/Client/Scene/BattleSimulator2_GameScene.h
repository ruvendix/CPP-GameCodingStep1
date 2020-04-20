// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2 게임 씬입니다.
// =====================================================================================

#ifndef BATTLE_SIMULATOR2_GAME_SCENE_H__
#define BATTLE_SIMULATOR2_GAME_SCENE_H__

#include "Element\Scene.h"
#include "Controller\ConsoleControllerEnum.h"
#include "MiniGame\BattleSimulator2\GameObject\ObjectState.h"

class Unit;
class BattleSimulator2World;
class BattleSimulator2_LevelDesign;

using UnitPtr = std::shared_ptr<Unit>;
using MapUnitStateCallback = MapCustom<EUnitState, std::function<void(UnitPtr)>>;

DECLARE_LOG_CATEGORY(BattleSimulator2_GameScene);
class BattleSimulator2_GameScene final : public Scene
{
	DECLARE_RTTI(BattleSimulator2_GameScene, Scene);

public:
#pragma region 생성자 및 소멸자
	using Scene::Scene;
	virtual ~BattleSimulator2_GameScene() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;

private:
	void OnCallback_UpdateIdleState(UnitPtr spUnit);
	void OnCallback_UpdateMoveState(UnitPtr spUnit);
	void OnCallback_UpdateAttackState(UnitPtr spUnit);
	void OnCallback_UpdateDeathState(UnitPtr spUnit);

	void OnTrigger_DeathUnit();
	void OnTrigger_BattleEnd() const;

	std::shared_ptr<BattleSimulator2World> m_spWorld = nullptr;
	std::shared_ptr<BattleSimulator2_LevelDesign> m_spLevelDesign = nullptr;
	std::vector<UnitPtr> m_vecUnit;
	std::queue<UnitPtr> m_queueDeathUnit;
	MapUnitStateCallback m_mapUnitStateCallback;

	bool m_bBattleEnd = false;
};

#endif