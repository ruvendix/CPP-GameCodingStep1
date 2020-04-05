// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ����� ������ ���Դϴ�.
// �⺻ ���忡 �پ��� ���� �������� ���� �� �ֽ��ϴ�.
// =====================================================================================

#ifndef BATTLE_SIMULATOR2_EDITOR_SCENE_H__
#define BATTLE_SIMULATOR2_EDITOR_SCENE_H__

#include "Element\Scene.h"
#include "Controller\ConsoleControllerEnum.h"
#include "MiniGame\BattleSimulator2\BattleSimulator2World.h"

class MenuTable_Row;

DECLARE_LOG_CATEGORY(BattleSimulator2_EditorScene);

class BattleSimulator2_EditorScene final : public Scene
{
	FRIEND_WITH_HELPER(BattleSimulator2_EditorSceneHelper);
	INPUT_FPS_LIMITED(8);

public:
#pragma region ������ �� �Ҹ���
	using Scene::Scene;
	virtual ~BattleSimulator2_EditorScene() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;

private:
	bool m_bMenuMode = true;
	std::shared_ptr<MenuTable_Row> m_spEditorMenuTable;
	std::unique_ptr<BattleSimulatorWorld> m_spWorld;
};

#endif