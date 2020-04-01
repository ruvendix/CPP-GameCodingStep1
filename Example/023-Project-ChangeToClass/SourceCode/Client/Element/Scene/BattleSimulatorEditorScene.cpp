// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터 에디터 씬입니다.
// 기본 월드에 다양한 레벨 디자인을 만들 수 있습니다.
// =====================================================================================

#include "PCH.h"
#include "BattleSimulatorEditorScene.h"

#include "Controller\FrameController.h"
#include "Controller\ConsoleController.h"
#include "Controller\InputController.h"
#include "Manager\SceneManager.h"
#include "Element\Scene\IntroMenuScene.h"

class BattleSimulatorEditorSceneHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(BattleSimulatorEditorSceneHelper);

public:
	static void DrawMenu(Int32 drawPosY);

	static void OnInput_MenuMode(_Inout_ BattleSimulatorEditorScene& targetHelper);
	static void OnInput_EditorMode(_Inout_ BattleSimulatorEditorScene& targetHelper);
};

void BattleSimulatorEditorSceneHelper::DrawMenu(Int32 drawPosY)
{
	PUT_STRING(84, ++drawPosY, "┏━━━━━━━━━━━━━━━━━━━━━┓");
	PUT_STRING(84, ++drawPosY, "┃    레벨 디자인 편집 ┃");
	PUT_STRING(84, ++drawPosY, "┃    레벨 디자인 저장 ┃");
	PUT_STRING(84, ++drawPosY, "┃    레벨 디자인 열기 ┃");
	PUT_STRING(84, ++drawPosY, "┃    게임 시작        ┃");
	PUT_STRING(84, ++drawPosY, "┗━━━━━━━━━━━━━━━━━━━━━┛");
}

void BattleSimulatorEditorSceneHelper::OnInput_MenuMode(_Inout_ BattleSimulatorEditorScene& targetHelper)
{
	if (InputController::I()->CheckInputState("GotoIntro", EInputMappingState::DOWN) == true)
	{
		SceneMgr::I()->CreateScene<IntroMenuScene>(ESceneType::NEXT);
	}

	if (InputController::I()->CheckInputState("SelectUp", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(-1);
		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("SelectUp 눌렀다!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+1);
		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("SelectDown 눌렀다!");
	}

	BEGIN_INPUT_FPS_LIMITED_HELPER(targetHelper);
	if (InputController::I()->CheckInputState("SelectUp", EInputMappingState::PRESSING) == true)
	{
		ConsoleController::I()->AddSelectorPosY(-1);
		DEBUG_LOG("SelectUp 누르는 중!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::PRESSING) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+1);
		DEBUG_LOG("SelectDown 누르는 중!");
	}
	END_INPUT_FPS_LIMITED();

	if (InputController::I()->CheckInputState("SelectMenu", EInputMappingState::DOWN) == true)
	{
		
		// 메뉴 하나하나를 클래스로 만들어서 받는 걸로...
		// 셀렉터의 현재 좌표와 최솟값을 이용해서 인덱스를 알아낼 수 있음!
		// 메뉴 묶음과 메뉴 클래스를 분리해서 클라에서는 메뉴 묶음으로 모든 걸 컨트롤

		DEBUG_LOG("SelectMenu 눌렀다!");
	}
}

void BattleSimulatorEditorSceneHelper::OnInput_EditorMode(_Inout_ BattleSimulatorEditorScene& targetHelper)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_LOG_CATEGORY(BattleSimulatorEditorScene);

EErrorType BattleSimulatorEditorScene::OnInitialize()
{
	DEBUG_LOG_CATEGORY(BattleSimulatorEditorScene, "배틀 시뮬레이터 에디터 씬!");
	InputController::I()->InsertInputMappingInfo("GotoIntro", VK_ESCAPE);
	InputController::I()->InsertInputMappingInfo("SelectUp", VK_UP);
	InputController::I()->InsertInputMappingInfo("SelectDown", VK_DOWN);
	InputController::I()->InsertInputMappingInfo("SelectLeft", VK_LEFT);
	InputController::I()->InsertInputMappingInfo("SelectRight", VK_RIGHT);
	InputController::I()->InsertInputMappingInfo("SelectMenu", VK_RETURN);

	m_spWorld = std::make_unique<BattleSimulatorWorld>(SizeInfo{ 40, 30 });

	// 월드 파일이 있는지?
	// 있다면 파일을 읽고, 아니면 새로 초기화해야 해요!
	EErrorType errorType = m_spWorld->LoadFile("BattleSimulatorWorld.world");
	if (errorType == EErrorType::LOAD_FILE_FAIL)
	{
		m_spWorld->setLastError(EErrorType::LOAD_FILE_FAIL);

		if (m_spWorld->OnInitialize() == EErrorType::INIT_FAIL)
		{
			return EErrorType::INIT_FAIL;
		}
	}

	return EErrorType::NONE;
}

EErrorType BattleSimulatorEditorScene::OnPostInitialize()
{
	if (m_spWorld->getLastError() == EErrorType::LOAD_FILE_FAIL)
	{
		if (m_spWorld->OnPostInitialize() == EErrorType::INIT_FAIL)
		{
			return EErrorType::INIT_FAIL;
		}

		m_spWorld->ResetError();
	}

	//// 세이브 테스트!
	//m_world->OnSaveFile("BattleSimulatorWorld.world");

	ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	consoleSelector.setSelectorPos(86, 12);
	consoleSelector.setMinSelectorPosY(12);
	consoleSelector.setMaxSelectorPosY(15);

	return EErrorType::NONE;
}

EErrorType BattleSimulatorEditorScene::OnInput()
{
	if (m_bMenuMode == true)
	{
		BattleSimulatorEditorSceneHelper::OnInput_MenuMode(*this);
	}
	else
	{
		BattleSimulatorEditorSceneHelper::OnInput_EditorMode(*this);
	}

	return EErrorType::NONE;
}

EErrorType BattleSimulatorEditorScene::OnUpdate()
{

	return EErrorType::NONE;
}

EErrorType BattleSimulatorEditorScene::OnRender()
{
	if (m_spWorld->OnRender() == EErrorType::RENDER_FAIL)
	{
		return EErrorType::RENDER_FAIL;
	}

	BattleSimulatorEditorSceneHelper::DrawMenu(10);

	ConsoleController::I()->DrawSelector();

	return EErrorType::NONE;
}

EErrorType BattleSimulatorEditorScene::OnFinalize()
{
	return EErrorType::NONE;
}
