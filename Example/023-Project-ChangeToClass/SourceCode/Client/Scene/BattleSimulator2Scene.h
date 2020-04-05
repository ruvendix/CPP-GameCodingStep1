// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2 ���Դϴ�.
// =====================================================================================

#ifndef BATTLE_SIMULATOR2_SCENE_H__
#define BATTLE_SIMULATOR2_SCENE_H__

#include "Element\Scene.h"
#include "Controller\ConsoleControllerEnum.h"
#include "MiniGame\BattleSimulator\BattleSimulatorWorld.h"

class MedievalKnight;
class Viking;

DECLARE_LOG_CATEGORY(BattleSimulator2Scene);

class BattleSimulator2Scene final : public Scene
{
	FRIEND_WITH_HELPER(BattleSimulator2SceneHelper);

public:
#pragma region ������ �� �Ҹ���
	using Scene::Scene;
	virtual ~BattleSimulator2Scene() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;

private:
	std::unique_ptr<BattleSimulatorWorld> m_world;
	std::vector<std::shared_ptr<MedievalKnight>> m_vecMedievalKnight;
	std::vector<std::shared_ptr<Viking>> m_vecViking;

	bool m_bBattleEnd = false;
};

#endif