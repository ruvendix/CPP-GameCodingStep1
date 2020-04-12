// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ��Ʈ�� ȭ���� �޴� ���Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "IntroMenuScene.h"

#include "Math\Random.h"
#include "Context\ConfigContext.h"
#include "Context\GameContext.h"
#include "Manager\SceneManager.h"
#include "Manager\TriggerTimerManager.h"
#include "Controller\InputController.h"
#include "Controller\ConsoleController.h"
#include "Controller\FrameController.h"
#include "IntroMenu\IntroMenu_Quit.h"
#include "IntroMenu\IntroMenu_SceneLoader.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace
{
	const Int32 RIGHT_MARGIN = 2;
	const Int32 MENU_MARGIN = 4;
	const Int32 MENU_BATTLE_SIMULATOR2_OFFSET_POS_Y = 2;
	const Int32 MENU_MISCELLANEOUS_SHOP2_OFFSET_POS_Y = MENU_BATTLE_SIMULATOR2_OFFSET_POS_Y + 2;
	const Int32 MENU_DIALOG_TREE_OFFSET_POS_Y = MENU_MISCELLANEOUS_SHOP2_OFFSET_POS_Y + 2;
	const Int32 MENU_QUIT_OFFSET_POS_Y = MENU_DIALOG_TREE_OFFSET_POS_Y + 2;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class IntroMenuSceneHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(IntroMenuSceneHelper);

public:
	using CompMenuInfoCallback = std::function<void(_Inout_ IntroMenuScene&, _Inout_ IntroMenu&)>;

	static void DrawScene(_Inout_ IntroMenuScene& helperTarget);
	static void DrawTitle(const IntroMenuScene& helperTarget);
	static void DrawSelector(const IntroMenuScene& helperTarget);
};

/*
��Ʈ�� ���� �޴� ���� �������մϴ�.
*/
void IntroMenuSceneHelper::DrawScene(_Inout_ IntroMenuScene& helperTarget)
{
	DrawTitle(helperTarget);
	helperTarget.m_spIntroMenuTable->DrawMenu();
	DrawSelector(helperTarget);
}

/*
��Ʈ�� ���� �޴� ���� Ÿ��Ʋ�� �������մϴ�.
*/
void IntroMenuSceneHelper::DrawTitle(const IntroMenuScene& helperTarget)
{
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, helperTarget.m_titleColorType);
	PUT_STRING(0, 0, "   _______  __   __  _______  __    _  _______  _______    _______  _______    _______  ___      _______  _______  _______ ");
	PUT_STRING(0, 1, "  |       ||  | |  ||   _   ||  |  | ||       ||       |  |       ||       |  |       ||   |    |   _   ||       ||       |");
	PUT_STRING(0, 2, "  |       ||  |_|  ||  |_|  ||   |_| ||    ___||    ___|  |_     _||   _   |  |       ||   |    |  |_|  ||  _____||  _____|");
	PUT_STRING(0, 3, "  |     __||       ||       ||       ||   | __ |   |___     |   |  |  | |  |  |     __||   |    |       || |_____ | |_____ ");
	PUT_STRING(0, 4, "  |    |__ |       ||       ||  _    ||   ||  ||    ___|    |   |  |  |_|  |  |    |__ |   |___ |       ||_____  ||_____  |");
	PUT_STRING(0, 5, "  |       ||   _   ||   _   || | |   ||   |_| ||   |___     |   |  |       |  |       ||       ||   _   | _____| | _____| |");
	PUT_STRING(0, 6, "  |_______||__| |__||__| |__||_|  |__||_______||_______|    |___|  |_______|  |_______||_______||__| |__||_______||_______|");
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::WHITE);
}

/*
��Ʈ�� ���� �޴� ���� �����͸� �������մϴ�.
*/
void IntroMenuSceneHelper::DrawSelector(const IntroMenuScene& helperTarget)
{
	// ���� ������ ��ȯ�� ���۵� ���� �ƴϰ�, ������ ������ ���� �ƴ϶�� �������� ��ǥ�� �����ؾ� �ؿ�!
	if ( (SceneMgr::I()->IsGotoNextScene() == false) &&
		 (helperTarget.m_bTerminateGame == false) )
	{
		std::shared_ptr<Menu> spCurrentMenu = helperTarget.m_spIntroMenuTable->getCurrentMenu();
		std::shared_ptr<Menu> spLongestMenu = helperTarget.m_spIntroMenuTable->getLongestMenu();

		helperTarget.m_spDblConsoleSelector->setSelectorPos(spLongestMenu->getPos().X - MENU_MARGIN, spCurrentMenu->getPos().Y);
		helperTarget.m_spDblConsoleSelector->setSecondSelectorOffsetPosX((2 * MENU_MARGIN) + spLongestMenu->getNameTag().size() - 2);

		ConsoleController::I()->ModifyCurrentConsoleSelectorPos(helperTarget.m_spDblConsoleSelector->getSelectorPos());
	}

	helperTarget.m_spDblConsoleSelector->OnDrawSelector();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_LOG_CATEGORY(IntroMenuScene);

EErrorType IntroMenuScene::OnInitialize()
{
	InputController::I()->InsertInputMappingInfo("Exit", VK_ESCAPE);

	m_spIntroMenuTable = std::make_unique<MenuTable_Row>();
	m_spIntroMenuTable->AddMenu(std::make_shared<IntroMenu_SceneLoader>("��Ʋ �ùķ����ͣ�", COORD{ 0, 0 },
		COORD{ -RIGHT_MARGIN, MENU_BATTLE_SIMULATOR2_OFFSET_POS_Y }, EMiniGameSceneType::BATTLE_SIMULATOR2));
	m_spIntroMenuTable->AddMenu(std::make_shared<IntroMenu_SceneLoader>("��ȭ ������", COORD{ 0, 0 },
		COORD{ -RIGHT_MARGIN, MENU_MISCELLANEOUS_SHOP2_OFFSET_POS_Y }, EMiniGameSceneType::MISCELLANEOUS_SHOP2));
	m_spIntroMenuTable->AddMenu(std::make_shared<IntroMenu_SceneLoader>("���̾�α� Ʈ��", COORD{ 0, 0 },
		COORD{ -RIGHT_MARGIN, MENU_DIALOG_TREE_OFFSET_POS_Y }, EMiniGameSceneType::DIALOG_TREE));
	m_spIntroMenuTable->AddMenu(std::make_shared<IntroMenu_Quit>("���� ����", COORD{ 0, 0 }, COORD{ -RIGHT_MARGIN, MENU_QUIT_OFFSET_POS_Y }));
	
	m_spIntroMenuTable->AlignCenterForMenu();

	m_spDblConsoleSelector = std::make_unique<DblConsoleSelector>();
	m_spDblConsoleSelector->setShape("��");
	m_spDblConsoleSelector->setSecondShape("��");

	TriggerTimerMgr::I()->AddTriggerTimer("ChangeIntroTitle",
		0.3f, 0.0f, this, &IntroMenuScene::OnTrigger_ChangeRandomColorToTitle, false, true);

	return EErrorType::NOTHING;
}

EErrorType IntroMenuScene::OnPostInitialize()
{
	// OnPostInitialize()�� �������� ��ǥ ���������� ����ҰԿ�!
	if (ConsoleController::I()->IsEmptySelector())
	{
		return EErrorType::NO_PREV_CONSOLE_SELECTOR;
	}

	ConsoleController::I()->RestoreConsoleSelector();

	COORD selectorPos = ConsoleController::I()->QueryCurrentConsoleSelectorPos();
	selectorPos.X += ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU;

	Int32 currentMenuIdx = m_spIntroMenuTable->ToMenuIdx(selectorPos, true);
	m_spIntroMenuTable->setCurrentMenuIdx(currentMenuIdx);

	return EErrorType::NOTHING;
}

EErrorType IntroMenuScene::OnInput()
{
	if (m_bTerminateGame == true)
	{
		return EErrorType::NOTHING;
	}

	m_spIntroMenuTable->OnInput();

	if (InputController::I()->CheckInputState("Exit", EInputMappingState::DOWN) == true)
	{
		std::shared_ptr<Menu> spPrevMenu = m_spIntroMenuTable->getCurrentMenu();
		m_spIntroMenuTable->setCurrentMenuIdx(m_spIntroMenuTable->getMenuCnt() - 1);
		m_spIntroMenuTable->ExcuteCurrentMenu();
		m_spDblConsoleSelector->setSelectorPosY(spPrevMenu->getPos().Y);

		m_bTerminateGame = true;
		DEBUG_LOG_CATEGORY(IntroMenuScene, "Exit ������!");
	}

	return EErrorType::NOTHING;
}

EErrorType IntroMenuScene::OnRender()
{
	IntroMenuSceneHelper::DrawScene(*this);
	return EErrorType::NOTHING;
}

EErrorType IntroMenuScene::OnFinalize()
{
	TriggerTimerMgr::I()->DeleteTriggerTimer("ChangeIntroTitle");
	InputController::I()->EnableInput();

	return EErrorType::NOTHING;
}

void IntroMenuScene::OnTrigger_ChangeRandomColorToTitle()
{
	m_titleColorType = static_cast<EConsoleOutputColorType>(
		math::RandomUtil::GenerateRandom(CommonFunc::ToUnderlyingType(EConsoleOutputColorType::BLUE),
			CommonFunc::ToUnderlyingType(EConsoleOutputColorType::BRIGHT_WHITE)));
}