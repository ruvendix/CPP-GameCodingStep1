// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʈ�� �޴� ������ ���Ǵ� ���� Ŭ�����Դϴ�.
// �������� �̿��ؼ� ���� �ε��մϴ�.
// =====================================================================================

#include "PCH.h"
#include "IntroMenu_SceneLoader.h"

#include "Manager\SceneManager.h"
#include "Manager\TriggerTimerManager.h"
#include "Controller\ConsoleController.h"
#include "Controller\InputController.h"

#include "Scene\BattleSimulator2_EditorScene.h"
#include "Scene\MiscellaneousShop2Scene.h"
#include "Scene\DialogTreeScene.h"

IntroMenu_SceneLoader::IntroMenu_SceneLoader(const std::string_view& szNameTag, const COORD& pos,
	const COORD& offsetCenterPos, EMiniGameSceneType miniGameSceneType) :
	Menu(szNameTag, pos, offsetCenterPos),
	m_selectedSceneType(miniGameSceneType)
{

}

EErrorType IntroMenu_SceneLoader::OnExcute()
{
	InputController::I()->DisableInput();
	TriggerTimerMgr::I()->AddTriggerTimer("Excute_IntroMenu_SceneLoader", 
		1.0f, 0.0f, this, &IntroMenu_SceneLoader::OnTrigger_Excute, false, false);

	return EErrorType::NOTHING;
}

void IntroMenu_SceneLoader::OnTrigger_Excute()
{
	ConsoleController::I()->PushBackupConsoleSelector();

	switch (m_selectedSceneType)
	{
	case EMiniGameSceneType::BATTLE_SIMULATOR2:
	{
		SceneMgr::I()->CreateScene<BattleSimulator2_EditorScene>(ECreateType::NEXT);
		break;
	}

	case EMiniGameSceneType::DIALOG_TREE:
	{
		SceneMgr::I()->CreateScene<DialogTreeScene>(ECreateType::NEXT);
		break;
	}

	case EMiniGameSceneType::MISCELLANEOUS_SHOP2:
	{
		SceneMgr::I()->CreateScene<MiscellaneousShop2Scene>(ECreateType::NEXT);
		break;
	}

	default:
	{
		DEFAULT_ERROR_HANDLER(EErrorType::UNKNOWN_SCENE_TYPE);
		break;
	}
	}
}
