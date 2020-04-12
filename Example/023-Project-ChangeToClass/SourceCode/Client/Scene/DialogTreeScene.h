// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 대화 트리 씬입니다.
// =====================================================================================

#ifndef DIALOG_TREE_SCENE_H__
#define DIALOG_TREE_SCENE_H__

#include "Element\Scene.h"
#include "Controller\ConsoleControllerEnum.h"
#include "MiniGame\DialogTree\DialogTree.h"

DECLARE_LOG_CATEGORY(DialogTreeScene);

class DialogTreeScene final : public Scene
{
	DECLARE_RTTI(DialogTreeScene, Scene);
	FRIEND_WITH_HELPER(DialogTreeSceneHelper);
	INPUT_FPS_LIMITED(8);

public:
#pragma region 생성자 및 소멸자
	using Scene::Scene;
	virtual ~DialogTreeScene() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnRender() override;

private:
	std::unique_ptr<DialogTree> m_spDialogTree;
	std::shared_ptr<DialogNode> m_spCurrentDialogNode;
};

#endif