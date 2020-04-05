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
#include "Element\Menu\Menu.h"
#include "Element\Menu\MenuTable_Row.h"

#include "Scene\IntroMenuScene.h"
#include "IntroMenu\IntroMenu_ComeBack.h"

namespace
{
	std::unique_ptr<UI_PosInfo> s_spUI_posInfo;
}

class BattleSimulatorEditorSceneHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(BattleSimulatorEditorSceneHelper);

public:
	static void DrawMenu(const COORD& pos, std::shared_ptr<MenuTable_Row> spMenuTable);

	static void OnInput_MenuMode(_Inout_ BattleSimulatorEditorScene& targetHelper);
	static void OnInput_EditorMode(_Inout_ BattleSimulatorEditorScene& targetHelper);
};

void BattleSimulatorEditorSceneHelper::DrawMenu(const COORD& pos, std::shared_ptr<MenuTable_Row> spMenuTable)
{
	Int32 drawPosX = pos.X;
	Int32 drawPosY = spMenuTable->getFirstMenu()->getPos().Y - 1;

#pragma region ���� ��輱
	PUT_STRING(drawPosX, drawPosY, "��");
	
	TSize drawLength =
		(spMenuTable->getLongestMenu()->getNameTag().size() / 2) + (ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU / 2) + 1;

	for (TSize i = 0; i < drawLength; ++i)
	{
		drawPosX += 2;
		PUT_STRING(drawPosX, drawPosY, "��");		
	}

	PUT_STRING(drawPosX, drawPosY, "��");
#pragma endregion

#pragma region ���� ��輱
	drawPosX = pos.X;
	TSize menuCnt = spMenuTable->getMenuCnt();
	for (TSize i = 0; i < menuCnt; ++i)
	{
		PUT_STRING(drawPosX, ++drawPosY, "��");
		PUT_STRING(drawPosX + (drawLength * 2), drawPosY, "��");
	}
#pragma endregion

#pragma region �Ʒ��� ��輱
	drawPosX = pos.X;
	PUT_STRING(drawPosX, ++drawPosY, "��");

	for (TSize i = 0; i < drawLength; ++i)
	{
		drawPosX += 2;
		PUT_STRING(drawPosX, drawPosY, "��");
	}

	PUT_STRING(drawPosX, drawPosY, "��");
#pragma endregion

	spMenuTable->DrawMenu();
}

void BattleSimulatorEditorSceneHelper::OnInput_MenuMode(_Inout_ BattleSimulatorEditorScene& targetHelper)
{
	targetHelper.m_spEditorMenuTable->OnInput();

	if (InputController::I()->CheckInputState("GotoIntro", EInputMappingState::DOWN) == true)
	{
		SceneMgr::I()->CreateScene<IntroMenuScene>(ECreateType::NEXT);
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

	s_spUI_posInfo = std::make_unique<UI_PosInfo>();
	s_spUI_posInfo->startPos = COORD{ 85, 10 };
	s_spUI_posInfo->menuStartPos = s_spUI_posInfo->startPos;
	s_spUI_posInfo->menuStartPos.X += ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU;
	s_spUI_posInfo->menuStartPos.Y += 1;
	s_spUI_posInfo->diffSize.height = 1;

	m_spEditorMenuTable = std::make_shared<MenuTable_Row>();
	m_spEditorMenuTable->AddMenu(std::make_shared<Menu>("���� ������ ����",
		COORD{ s_spUI_posInfo->menuStartPos.X, s_spUI_posInfo->menuStartPos.Y }));

	Int32 diffMultipleFactor = 0;
	m_spEditorMenuTable->AddMenu(std::make_shared<Menu>("���� ������ ����",
		COORD{ s_spUI_posInfo->menuStartPos.X,
		s_spUI_posInfo->menuStartPos.Y + static_cast<SHORT>(s_spUI_posInfo->diffSize.height * (++diffMultipleFactor)) }));

	m_spEditorMenuTable->AddMenu(std::make_shared<Menu>("���� ������ ����",
		COORD{ s_spUI_posInfo->menuStartPos.X,
		s_spUI_posInfo->menuStartPos.Y + static_cast<SHORT>(s_spUI_posInfo->diffSize.height * (++diffMultipleFactor)) }));

	m_spEditorMenuTable->AddMenu(std::make_shared<Menu>("���� ����",
		COORD{ s_spUI_posInfo->menuStartPos.X,
		s_spUI_posInfo->menuStartPos.Y + static_cast<SHORT>(s_spUI_posInfo->diffSize.height * (++diffMultipleFactor)) }));

	m_spEditorMenuTable->AddMenu(std::make_shared<IntroMenu_ComeBack>("������",
		COORD{ s_spUI_posInfo->menuStartPos.X,
		s_spUI_posInfo->menuStartPos.Y + static_cast<SHORT>(s_spUI_posInfo->diffSize.height * (++diffMultipleFactor)) }));

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
	consoleSelector.setSelectorPos(
		s_spUI_posInfo->startPos.X + ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_BORDER, s_spUI_posInfo->menuStartPos.Y);
	consoleSelector.setMinSelectorPosY(s_spUI_posInfo->startPos.Y);
	consoleSelector.setMaxSelectorPosY(s_spUI_posInfo->startPos.Y + m_spEditorMenuTable->getLastIdx());

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

	BattleSimulatorEditorSceneHelper::DrawMenu(s_spUI_posInfo->startPos, m_spEditorMenuTable);

	ConsoleController::I()->DrawSelector();

	return EErrorType::NONE;
}

EErrorType BattleSimulatorEditorScene::OnFinalize()
{
	return EErrorType::NONE;
}
