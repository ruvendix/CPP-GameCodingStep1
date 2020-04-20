// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2 ���� ���Դϴ�.
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
#pragma region ������ �� �Ҹ���
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