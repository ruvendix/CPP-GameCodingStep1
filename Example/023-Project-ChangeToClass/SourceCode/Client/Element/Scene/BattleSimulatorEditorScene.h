// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터 에디터 씬입니다.
// 기본 월드에 다양한 레벨 디자인을 만들 수 있습니다.
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
#pragma region 생성자 및 소멸자
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