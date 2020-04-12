// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 게임 인트로 화면의 메뉴 씬입니다.
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
인트로 게임 메뉴 씬을 렌더링합니다.
*/
void IntroMenuSceneHelper::DrawScene(_Inout_ IntroMenuScene& helperTarget)
{
	DrawTitle(helperTarget);
	helperTarget.m_spIntroMenuTable->DrawMenu();
	DrawSelector(helperTarget);
}

/*
인트로 게임 메뉴 씬의 타이틀을 렌더링합니다.
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
인트로 게임 메뉴 씬의 셀렉터를 렌더링합니다.
*/
void IntroMenuSceneHelper::DrawSelector(const IntroMenuScene& helperTarget)
{
	// 다음 씬으로 전환이 시작될 때도 아니고, 게임을 종료할 때도 아니라면 셀렉터의 좌표를 갱신해야 해요!
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
	m_spIntroMenuTable->AddMenu(std::make_shared<IntroMenu_SceneLoader>("배틀 시뮬레이터２", COORD{ 0, 0 },
		COORD{ -RIGHT_MARGIN, MENU_BATTLE_SIMULATOR2_OFFSET_POS_Y }, EMiniGameSceneType::BATTLE_SIMULATOR2));
	m_spIntroMenuTable->AddMenu(std::make_shared<IntroMenu_SceneLoader>("잡화 상점２", COORD{ 0, 0 },
		COORD{ -RIGHT_MARGIN, MENU_MISCELLANEOUS_SHOP2_OFFSET_POS_Y }, EMiniGameSceneType::MISCELLANEOUS_SHOP2));
	m_spIntroMenuTable->AddMenu(std::make_shared<IntroMenu_SceneLoader>("다이얼로그 트리", COORD{ 0, 0 },
		COORD{ -RIGHT_MARGIN, MENU_DIALOG_TREE_OFFSET_POS_Y }, EMiniGameSceneType::DIALOG_TREE));
	m_spIntroMenuTable->AddMenu(std::make_shared<IntroMenu_Quit>("게임 종료", COORD{ 0, 0 }, COORD{ -RIGHT_MARGIN, MENU_QUIT_OFFSET_POS_Y }));
	
	m_spIntroMenuTable->AlignCenterForMenu();

	m_spDblConsoleSelector = std::make_unique<DblConsoleSelector>();
	m_spDblConsoleSelector->setShape("◀");
	m_spDblConsoleSelector->setSecondShape("▶");

	TriggerTimerMgr::I()->AddTriggerTimer("ChangeIntroTitle",
		0.3f, 0.0f, this, &IntroMenuScene::OnTrigger_ChangeRandomColorToTitle, false, true);

	return EErrorType::NOTHING;
}

EErrorType IntroMenuScene::OnPostInitialize()
{
	// OnPostInitialize()는 셀렉터의 좌표 복원용으로 사용할게요!
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
		DEBUG_LOG_CATEGORY(IntroMenuScene, "Exit 눌렀다!");
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