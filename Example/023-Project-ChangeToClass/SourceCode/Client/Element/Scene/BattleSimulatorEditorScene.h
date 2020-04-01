// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ����� ������ ���Դϴ�.
// �⺻ ���忡 �پ��� ���� �������� ���� �� �ֽ��ϴ�.
// =====================================================================================

#ifndef BATTLE_SIMULATOR_EDITOR_SCENE_H__
#define BATTLE_SIMULATOR_EDITOR_SCENE_H__

#include "Element\Scene.h"
#include "Controller\ConsoleControllerEnum.h"
#include "MiniGame\BattleSimulator\BattleSimulatorWorld.h"

DECLARE_LOG_CATEGORY(BattleSimulatorEditorScene);

class BattleSimulatorEditorScene final : public Scene
{
	FRIEND_WITH_HELPER(BattleSimulatorEditorSceneHelper);
	INPUT_FPS_LIMITED(8);

public:
#pragma region ������ �� �Ҹ���
	using Scene::Scene;
	virtual ~BattleSimulatorEditorScene() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;

private:
	bool m_bMenuMode = true;
	std::unique_ptr<BattleSimulatorWorld> m_spWorld;
};

#endif