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
#include "Controller\FrameController.h"
#include "Controller\ConsoleController.h"
#include "IntroMenuSceneAssist\IntroMenu_Quit.h"
#include "IntroMenuSceneAssist\IntroMenu_SceneLoader.h"

namespace
{
	const Int32 SCENE_RIGHT_MARGIN_LENGTH = 2;
	const Int32 MENU_MARGIN_LENGTH = 4;
	const Int32 MENU_BATTLE_SIMULATOR_OFFSET_POS_Y = 2;
	const Int32 MENU_MISCELLANEOUS_SHOP2_OFFSET_POS_Y = MENU_BATTLE_SIMULATOR_OFFSET_POS_Y + 2;
	const Int32 MENU_DIALOGUE_TREE_OFFSET_POS_Y = MENU_MISCELLANEOUS_SHOP2_OFFSET_POS_Y + 2;
	const Int32 MENU_QUIT_OFFSET_POS_Y = MENU_DIALOGUE_TREE_OFFSET_POS_Y + 2;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class IntroMenuSceneHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(IntroMenuSceneHelper);

public:
	using CompMenuInfoCallback = std::function<void(_Inout_ IntroMenuScene&, _Inout_ IntroMenu&)>;

	static void DrawScene(_Inout_ IntroMenuScene& helperTarget);
	static void DrawTitle(const IntroMenuScene& helperTarget);
	static void DrawAllMenu(_Inout_ IntroMenuScene& helperTarget);
	static void DrawSelector(const IntroMenuScene& helperTarget);
	static void AlignCenterMenu(_Inout_ IntroMenuScene& helperTarget, _Inout_ IntroMenu& gameIntroMenu);
	
	static void ResetCallback_CompMenuInfo();
	static void OnCallback_CompMenuInfo_QueryLongest(_Inout_ IntroMenuScene& helperTarget, _Inout_ IntroMenu& gameIntroMenu);
	static void OnCallback_CompMenuInfo_None(_Inout_ IntroMenuScene& helperTarget, _Inout_ IntroMenu& gameIntroMenu);

	static Int32 ToMenuIdx(Int32 y);

private:
	static CompMenuInfoCallback m_compMenuInfoCallback; // 전략 패턴
};

// 헬퍼 클래스의 멤버변수는 콜백과 상수만 넣을게요!
// 다른 용도의 멤버변수를 넣게 되면 static이라 모든 인스턴스가 공유해버려서 망해요...
IntroMenuSceneHelper::CompMenuInfoCallback IntroMenuSceneHelper::m_compMenuInfoCallback = OnCallback_CompMenuInfo_QueryLongest;

/*
인트로 게임 메뉴 씬을 렌더링합니다.
*/
void IntroMenuSceneHelper::DrawScene(_Inout_ IntroMenuScene& helperTarget)
{
	DrawTitle(helperTarget);
	DrawAllMenu(helperTarget);

	// 가장 긴 메뉴 정보를 알아냈다면 더 이상 업데이트하지 않습니다!
	if (std::get<2>(helperTarget.m_tupleLongestMenuInfo) == false)
	{
		std::get<2>(helperTarget.m_tupleLongestMenuInfo) = true;
		m_compMenuInfoCallback = OnCallback_CompMenuInfo_None;
	}

	DrawSelector(helperTarget);
}

/*
인트로 게임 메뉴 씬의 타이틀을 렌더링합니다.
*/
void IntroMenuSceneHelper::DrawTitle(const IntroMenuScene& helperTarget)
{
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, helperTarget.m_titleColorType);
	PRINTF(0, 0, "   _______  __   __  _______  __    _  _______  _______    _______  _______    _______  ___      _______  _______  _______ ");
	PRINTF(0, 1, "  |       ||  | |  ||   _   ||  |  | ||       ||       |  |       ||       |  |       ||   |    |   _   ||       ||       |");
	PRINTF(0, 2, "  |       ||  |_|  ||  |_|  ||   |_| ||    ___||    ___|  |_     _||   _   |  |       ||   |    |  |_|  ||  _____||  _____|");
	PRINTF(0, 3, "  |     __||       ||       ||       ||   | __ |   |___     |   |  |  | |  |  |     __||   |    |       || |_____ | |_____ ");
	PRINTF(0, 4, "  |    |__ |       ||       ||  _    ||   ||  ||    ___|    |   |  |  |_|  |  |    |__ |   |___ |       ||_____  ||_____  |");
	PRINTF(0, 5, "  |       ||   _   ||   _   || | |   ||   |_| ||   |___     |   |  |       |  |       ||       ||   _   | _____| | _____| |");
	PRINTF(0, 6, "  |_______||__| |__||__| |__||_|  |__||_______||_______|    |___|  |_______|  |_______||_______||__| |__||_______||_______|");
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::WHITE);
}

/*
인트로 게임 메뉴 씬의 모든 메뉴를 렌더링합니다.
*/
void IntroMenuSceneHelper::DrawAllMenu(_Inout_ IntroMenuScene& helperTarget)
{
	for (auto& iter : helperTarget.m_vecIntroMenu)
	{
		if (iter == nullptr)
		{
			continue;
		}

		AlignCenterMenu(helperTarget, *iter);

		COORD currentConsolePos = ConsoleController::I()->QueryCurrentConsolePos();
		PRINTF(currentConsolePos.X, currentConsolePos.Y, "%s", iter->getNameTag().c_str());
	}
}

/*
인트로 게임 메뉴 씬의 셀렉터를 렌더링합니다.
*/
void IntroMenuSceneHelper::DrawSelector(const IntroMenuScene& helperTarget)
{	
	const std::string_view& szLongestMenuName = std::get<0>(helperTarget.m_tupleLongestMenuInfo);
	const COORD& longestMenuPos = std::get<1>(helperTarget.m_tupleLongestMenuInfo);
	std::shared_ptr spGameIntroMenu = helperTarget.m_vecIntroMenu[helperTarget.m_selectedIntroMenuIdx];

	helperTarget.m_spDblConsoleSelector->setSelectorPos(longestMenuPos.X - MENU_MARGIN_LENGTH, spGameIntroMenu->getPos().Y);
	helperTarget.m_spDblConsoleSelector->setSecondSelectorOffsetPosX((2 * MENU_MARGIN_LENGTH) + szLongestMenuName.size() - 2);

	// 다음 씬으로 전환이 시작될 때는 셀렉터의 좌표를 갱신하지 않아야 해요!
	if (SceneMgr::I()->IsGotoNextScene() == false)
	{
		ConsoleController::I()->SetCurrentConsoleSelectorPos(helperTarget.m_spDblConsoleSelector->getSelectorPos());
	}

	helperTarget.m_spDblConsoleSelector->OnDrawSelector();
}

/*
인트로 게임 메뉴 씬의 메뉴를 중앙 정렬합니다.
*/
void IntroMenuSceneHelper::AlignCenterMenu(_Inout_ IntroMenuScene& helperTarget, _Inout_ IntroMenu& gameIntroMenu)
{
	ConsoleController::I()->AlignCenter(ConfigCtx::I()->getResoultion(), gameIntroMenu.getNameTag().size());

	// 이동된 중앙 정렬 좌표에서 오프셋만큼 이동!
	COORD currentPos = ConsoleController::I()->QueryCurrentConsolePos();
	currentPos.X += gameIntroMenu.getOffsetCenterPos().X;
	currentPos.Y += gameIntroMenu.getOffsetCenterPos().Y;

	gameIntroMenu.setPos(currentPos);
	ConsoleController::I()->MoveConsolePos(currentPos);

	m_compMenuInfoCallback(helperTarget, gameIntroMenu);
}

/*
전달받은 메뉴 정보와 비교하면서 가장 긴 메뉴 정보를 알아냅니다.
*/
void IntroMenuSceneHelper::OnCallback_CompMenuInfo_QueryLongest(_Inout_ IntroMenuScene& helperTarget, _Inout_ IntroMenu& gameIntroMenu)
{
	const COORD& menuPos = gameIntroMenu.getPos();

	Int32 longestMenuPosX = std::get<1>(helperTarget.m_tupleLongestMenuInfo).X;
	if ( (longestMenuPosX == SHRT_MIN) || // 처음 정보를 갱신할 때에요!
		 (menuPos.X < longestMenuPosX) )
	{
		std::get<0>(helperTarget.m_tupleLongestMenuInfo) = gameIntroMenu.getNameTag();
		std::get<1>(helperTarget.m_tupleLongestMenuInfo) = menuPos;
	}
}

/*
가장 긴 메뉴 정보를 알아낸 후이므로 아무것도 하지 않습니다.
*/
void IntroMenuSceneHelper::OnCallback_CompMenuInfo_None(_Inout_ IntroMenuScene& helperTarget, _Inout_ IntroMenu& gameIntroMenu)
{

}

/*
콜백함수를 리셋합니다.
*/
void IntroMenuSceneHelper::ResetCallback_CompMenuInfo()
{
	m_compMenuInfoCallback = OnCallback_CompMenuInfo_QueryLongest;
}

Int32 IntroMenuSceneHelper::ToMenuIdx(Int32 y)
{
	ConsoleController::I()->AlignCenter(ConfigCtx::I()->getResoultion(), 0);
	Int32 currentConsolePosY = ConsoleController::I()->QueryCurrentConsolePos().Y;

	if (y == (currentConsolePosY + MENU_BATTLE_SIMULATOR_OFFSET_POS_Y))
	{
		return 0;
	}
	else if (y == (currentConsolePosY + MENU_MISCELLANEOUS_SHOP2_OFFSET_POS_Y))
	{
		return 1;
	}
	else if (y == (currentConsolePosY + MENU_DIALOGUE_TREE_OFFSET_POS_Y))
	{
		return 2;
	}
	else if (y == (currentConsolePosY + MENU_QUIT_OFFSET_POS_Y))
	{
		return 3;
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_LOG_CATEGORY(IntroMenuScene);

EErrorType IntroMenuScene::OnInitialize()
{
	InputController::I()->InsertInputMappingInfo("SelectUp", VK_UP);
	InputController::I()->InsertInputMappingInfo("SelectDown", VK_DOWN);
	InputController::I()->InsertInputMappingInfo("SelectMenu", VK_RETURN);
	InputController::I()->InsertInputMappingInfo("Exit", VK_ESCAPE);

	m_tupleLongestMenuInfo = std::make_tuple("Default", COORD{ SHRT_MIN, SHRT_MIN }, false);

	m_vecIntroMenu.push_back(std::make_shared<IntroMenu_SceneLoader>("배틀 시뮬레이터",
		COORD{ -SCENE_RIGHT_MARGIN_LENGTH, MENU_BATTLE_SIMULATOR_OFFSET_POS_Y }, EIntroMenu_SceneLoaderType::BATTLE_SIMULATOR));
	m_vecIntroMenu.push_back(std::make_shared<IntroMenu_SceneLoader>("잡화 상점２",
		COORD{ -SCENE_RIGHT_MARGIN_LENGTH, MENU_MISCELLANEOUS_SHOP2_OFFSET_POS_Y }, EIntroMenu_SceneLoaderType::MISCELLANEOUS_SHOP2));
	m_vecIntroMenu.push_back(std::make_shared<IntroMenu_SceneLoader>("다이얼로그 트리",
		COORD{ -SCENE_RIGHT_MARGIN_LENGTH, MENU_DIALOGUE_TREE_OFFSET_POS_Y }, EIntroMenu_SceneLoaderType::DIALOGUE_TREE));
	m_vecIntroMenu.push_back(std::make_shared<IntroMenu_Quit>("게임 종료", COORD{ -SCENE_RIGHT_MARGIN_LENGTH, MENU_QUIT_OFFSET_POS_Y }));

	m_spDblConsoleSelector = std::make_unique<DblConsoleSelector>();
	m_spDblConsoleSelector->setShape("◀");
	m_spDblConsoleSelector->setSecondShape("▶");

	TriggerTimerMgr::I()->AddTriggerTimer("ChangeIntroTitle", 0.3f, 0.0f, this, &IntroMenuScene::OnTrigger_ChangeRandomColorToTitle, false, true);
	IntroMenuSceneHelper::ResetCallback_CompMenuInfo();

	return EErrorType::NONE;
}

EErrorType IntroMenuScene::OnPostInitialize()
{
	if (ConsoleController::I()->IsEmptySelector())
	{
		return EErrorType::NO_PREV_CONSOLE_SELECTOR;
	}

	ConsoleController::I()->RestoreConsoleSelector();
	ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	m_selectedIntroMenuIdx = IntroMenuSceneHelper::ToMenuIdx(consoleSelector.getSelectorPos().Y);

	return EErrorType::NONE;
}

EErrorType IntroMenuScene::OnUpdate()
{
	if (InputController::I()->CheckInputState("SelectUp", EInputMappingState::DOWN) == true)
	{
		--m_selectedIntroMenuIdx;
		m_selectedIntroMenuIdx = math::ClampCycle(m_selectedIntroMenuIdx, 0, m_vecIntroMenu.size() - 1);
		m_localTime = 0.0f;
		DEBUG_LOG_CATEGORY(IntroMenuScene, "SelectUp 눌렀다!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::DOWN) == true)
	{
		++m_selectedIntroMenuIdx;
		m_selectedIntroMenuIdx = math::ClampCycle(m_selectedIntroMenuIdx, 0, m_vecIntroMenu.size() - 1);
		m_localTime = 0.0f;
		DEBUG_LOG_CATEGORY(IntroMenuScene, "SelectDown 눌렀다!");
	}

	BEGIN_FRAME_UPDATE_LIMITED();
	if (InputController::I()->CheckInputState("SelectUp", EInputMappingState::PRESSING) == true)
	{
		--m_selectedIntroMenuIdx;
		m_selectedIntroMenuIdx = math::ClampCycle(m_selectedIntroMenuIdx, 0, m_vecIntroMenu.size() - 1);
		DEBUG_LOG_CATEGORY(IntroMenuScene, "SelectUp 누르는 중!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::PRESSING) == true)
	{
		++m_selectedIntroMenuIdx;
		m_selectedIntroMenuIdx = math::ClampCycle(m_selectedIntroMenuIdx, 0, m_vecIntroMenu.size() - 1);
		DEBUG_LOG_CATEGORY(IntroMenuScene, "SelectDown 누르는 중!");
	}
	END_FRAME_UPDATE_LIMITED();

	if (InputController::I()->CheckInputState("SelectMenu", EInputMappingState::DOWN) == true)
	{
		TriggerTimerMgr::I()->AddTriggerTimer("ExcuteMenu", 1.0f, 0.0f, this, &IntroMenuScene::OnTrigger_ExcuteMenu, false, false);
		ConsoleController::I()->PushBackupConsoleSelector();
		DEBUG_LOG_CATEGORY(IntroMenuScene, "SelectMenu 눌렀다!");
	}

	if (InputController::I()->CheckInputState("Exit", EInputMappingState::DOWN) == true)
	{
		m_vecIntroMenu[static_cast<Int32>(m_vecIntroMenu.size() - 1)]->OnExcute();
		DEBUG_LOG_CATEGORY(IntroMenuScene, "Exit 눌렀다!");
	}
	
	return EErrorType::NONE;
}

EErrorType IntroMenuScene::OnRender()
{
	IntroMenuSceneHelper::DrawScene(*this);
	return EErrorType::NONE;
}

EErrorType IntroMenuScene::OnFinalize()
{
	TriggerTimerMgr::I()->DeleteTriggerTimer("ChangeIntroTitle");
	return EErrorType::NONE;
}

void IntroMenuScene::OnTrigger_ChangeRandomColorToTitle()
{
	m_titleColorType = static_cast<EConsoleOutputColorType>(
		math::RandomUtil::GenerateUniformDistribution(CommonFunc::ToUnderlyingType(EConsoleOutputColorType::BLUE),
			CommonFunc::ToUnderlyingType(EConsoleOutputColorType::BRIGHT_WHITE)));
}

void IntroMenuScene::OnTrigger_ExcuteMenu()
{
	CHECK_NULLPTR(m_vecIntroMenu[m_selectedIntroMenuIdx]);
	m_vecIntroMenu[m_selectedIntroMenuIdx]->OnExcute();
}