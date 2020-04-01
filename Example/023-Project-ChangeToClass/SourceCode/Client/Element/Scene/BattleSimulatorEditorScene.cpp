// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ����� ������ ���Դϴ�.
// �⺻ ���忡 �پ��� ���� �������� ���� �� �ֽ��ϴ�.
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
	PUT_STRING(84, ++drawPosY, "����������������������������������������������");
	PUT_STRING(84, ++drawPosY, "��    ���� ������ ���� ��");
	PUT_STRING(84, ++drawPosY, "��    ���� ������ ���� ��");
	PUT_STRING(84, ++drawPosY, "��    ���� ������ ���� ��");
	PUT_STRING(84, ++drawPosY, "��    ���� ����        ��");
	PUT_STRING(84, ++drawPosY, "����������������������������������������������");
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
		DEBUG_LOG("SelectUp ������!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+1);
		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("SelectDown ������!");
	}

	BEGIN_INPUT_FPS_LIMITED_HELPER(targetHelper);
	if (InputController::I()->CheckInputState("SelectUp", EInputMappingState::PRESSING) == true)
	{
		ConsoleController::I()->AddSelectorPosY(-1);
		DEBUG_LOG("SelectUp ������ ��!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::PRESSING) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+1);
		DEBUG_LOG("SelectDown ������ ��!");
	}
	END_INPUT_FPS_LIMITED();

	if (InputController::I()->CheckInputState("SelectMenu", EInputMappingState::DOWN) == true)
	{
		
		// �޴� �ϳ��ϳ��� Ŭ������ ���� �޴� �ɷ�...
		// �������� ���� ��ǥ�� �ּڰ��� �̿��ؼ� �ε����� �˾Ƴ� �� ����!
		// �޴� ������ �޴� Ŭ������ �и��ؼ� Ŭ�󿡼��� �޴� �������� ��� �� ��Ʈ��

		DEBUG_LOG("SelectMenu ������!");
	}
}

void BattleSimulatorEditorSceneHelper::OnInput_EditorMode(_Inout_ BattleSimulatorEditorScene& targetHelper)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_LOG_CATEGORY(BattleSimulatorEditorScene);

EErrorType BattleSimulatorEditorScene::OnInitialize()
{
	DEBUG_LOG_CATEGORY(BattleSimulatorEditorScene, "��Ʋ �ùķ����� ������ ��!");
	InputController::I()->InsertInputMappingInfo("GotoIntro", VK_ESCAPE);
	InputController::I()->InsertInputMappingInfo("SelectUp", VK_UP);
	InputController::I()->InsertInputMappingInfo("SelectDown", VK_DOWN);
	InputController::I()->InsertInputMappingInfo("SelectLeft", VK_LEFT);
	InputController::I()->InsertInputMappingInfo("SelectRight", VK_RIGHT);
	InputController::I()->InsertInputMappingInfo("SelectMenu", VK_RETURN);

	m_spWorld = std::make_unique<BattleSimulatorWorld>(SizeInfo{ 40, 30 });

	// ���� ������ �ִ���?
	// �ִٸ� ������ �а�, �ƴϸ� ���� �ʱ�ȭ�ؾ� �ؿ�!
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

	//// ���̺� �׽�Ʈ!
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
