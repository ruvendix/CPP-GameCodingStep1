// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��ȭ Ʈ�� ���Դϴ�.
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
#pragma region ������ �� �Ҹ���
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