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

class BattleSimulator2World;
class BattleSimulator2_LevelDesign;
class Unit;

DECLARE_LOG_CATEGORY(BattleSimulator2_GameScene);

class BattleSimulator2_GameScene final : public Scene
{
	DECLARE_RTTI(BattleSimulator2_GameScene, Scene);
	FRIEND_WITH_HELPER(BattleSimulator2_GameSceneHelper);

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
	void OnTrigger_DieUnit();
	void OnTrigger_PostDieUnit();
	void OnTrigger_BattleEnd() const;

	std::shared_ptr<BattleSimulator2World> m_spWorld = nullptr;
	std::shared_ptr<BattleSimulator2_LevelDesign> m_spLevelDesign = nullptr;
	std::vector<std::shared_ptr<Unit>> m_vecUnit;

	bool m_bBattleEnd = false;
};

#endif