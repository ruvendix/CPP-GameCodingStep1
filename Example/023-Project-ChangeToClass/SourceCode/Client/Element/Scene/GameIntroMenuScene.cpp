// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 게임 인트로 화면의 메뉴 씬입니다.
// =====================================================================================

#include "PCH.h"
#include "GameIntroMenuScene.h"

#include "Context\ConfigContext.h"
#include "Context\GameContext.h"
#include "Manager\SceneManager.h"
#include "Manager\TriggerTimerManager.h"
#include "Controller\InputController.h"
#include "Controller\ConsoleController.h"
#include "Controller\FrameController.h"

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

class GameIntroMenuSceneHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(GameIntroMenuSceneHelper);

public:
	using QueryLongestMenuInfoCallback = std::function<void(_Inout_ GameIntroMenuScene&, _Inout_ GameIntroMenu&)>;

	static void DrawScene(_Inout_ GameIntroMenuScene& helperTarget);
	static void DrawTitle();
	static void DrawAllMenu(_Inout_ GameIntroMenuScene& helperTarget);
	static void DrawSelector(const GameIntroMenuScene& helperTarget);
	static void AlignCenterMenu(_Inout_ GameIntroMenuScene& helperTarget, _Inout_ GameIntroMenu& gameIntroMenu);
	
	static void OnCallback_QueryLongestMenuInfo(_Inout_ GameIntroMenuScene& helperTarget, _Inout_ GameIntroMenu& gameIntroMenu);
	static void OnCallback_NonQueryLongestMenuInfo(_Inout_ GameIntroMenuScene& helperTarget, _Inout_ GameIntroMenu& gameIntroMenu);

private:
	static QueryLongestMenuInfoCallback m_queryLongestMenuInfoCallback; // 전략 패턴
};

// 헬퍼 클래스의 멤버변수는 콜백과 상수만 넣을게요!
// 다른 용도의 멤버변수를 넣게 되면 static이라 모든 인스턴스가 공유해버려서 망해요...
GameIntroMenuSceneHelper::QueryLongestMenuInfoCallback GameIntroMenuSceneHelper::m_queryLongestMenuInfoCallback = OnCallback_QueryLongestMenuInfo;

/*
인트로 게임 메뉴 씬을 렌더링합니다.
*/
void GameIntroMenuSceneHelper::DrawScene(_Inout_ GameIntroMenuScene& helperTarget)
{
	DrawTitle();
	DrawAllMenu(helperTarget);

	// 가장 긴 메뉴 정보를 알아냈다면 더 이상 업데이트하지 않습니다!
	if (std::get<2>(helperTarget.m_tupleLongestMenuInfo) == true)
	{
		std::get<2>(helperTarget.m_tupleLongestMenuInfo) = false;
		m_queryLongestMenuInfoCallback = OnCallback_NonQueryLongestMenuInfo;
	}

	DrawSelector(helperTarget);
}

/*
인트로 게임 메뉴 씬의 타이틀을 렌더링합니다.
*/
void GameIntroMenuSceneHelper::DrawTitle()
{
	PRINTF(0, 0, "   _______  __   __  _______  __    _  _______  _______    _______  _______    _______  ___      _______  _______  _______ ");
	PRINTF(0, 1, "  |       ||  | |  ||   _   ||  |  | ||       ||       |  |       ||       |  |       ||   |    |   _   ||       ||       |");
	PRINTF(0, 2, "  |       ||  |_|  ||  |_|  ||   |_| ||    ___||    ___|  |_     _||   _   |  |       ||   |    |  |_|  ||  _____||  _____|");
	PRINTF(0, 3, "  |     __||       ||       ||       ||   | __ |   |___     |   |  |  | |  |  |     __||   |    |       || |_____ | |_____ ");
	PRINTF(0, 4, "  |    |__ |       ||       ||  _    ||   ||  ||    ___|    |   |  |  |_|  |  |    |__ |   |___ |       ||_____  ||_____  |");
	PRINTF(0, 5, "  |       ||   _   ||   _   || | |   ||   |_| ||   |___     |   |  |       |  |       ||       ||   _   | _____| | _____| |");
	PRINTF(0, 6, "  |_______||__| |__||__| |__||_|  |__||_______||_______|    |___|  |_______|  |_______||_______||__| |__||_______||_______|");
}

/*
인트로 게임 메뉴 씬의 모든 메뉴를 렌더링합니다.
*/
void GameIntroMenuSceneHelper::DrawAllMenu(_Inout_ GameIntroMenuScene& helperTarget)
{
	for (auto& iter : helperTarget.m_vecGameIntroMenu)
	{
		if (iter == nullptr)
		{
			continue;
		}

		AlignCenterMenu(helperTarget, *iter);

		COORD currentConsolePos = ConsoleController::I()->GetCurrentConsolePos();
		PRINTF(currentConsolePos.X, currentConsolePos.Y, "%s", iter->getNameTag().c_str());
	}
}

/*
인트로 게임 메뉴 씬의 셀렉터를 렌더링합니다.
*/
void GameIntroMenuSceneHelper::DrawSelector(const GameIntroMenuScene& helperTarget)
{	
	const std::string_view& strLongestMenuName = std::get<0>(helperTarget.m_tupleLongestMenuInfo);
	const COORD& longestMenuPos = std::get<1>(helperTarget.m_tupleLongestMenuInfo);

	GameIntroMenu* pGameIntroMenu = helperTarget.m_vecGameIntroMenu[helperTarget.m_selectedGameIntroMenuIdx];
	CHECK_NULLPTR(pGameIntroMenu);

	PRINTF(longestMenuPos.X - MENU_MARGIN_LENGTH, pGameIntroMenu->getPos().Y, "◀");
	PRINTF(longestMenuPos.X + strLongestMenuName.size() + MENU_MARGIN_LENGTH - 2, pGameIntroMenu->getPos().Y, "▶");
}

/*
인트로 게임 메뉴 씬의 메뉴를 중앙 정렬합니다.
*/
void GameIntroMenuSceneHelper::AlignCenterMenu(_Inout_ GameIntroMenuScene& helperTarget, _Inout_ GameIntroMenu& gameIntroMenu)
{
	ConsoleController::I()->AlignCenter(ConfigCtx::I()->getResoultion(), gameIntroMenu.getNameTag().size());

	// 이동된 중앙 정렬 좌표에서 오프셋만큼 이동!
	COORD currentPos = ConsoleController::I()->GetCurrentConsolePos();
	currentPos.X += gameIntroMenu.getOffsetCenterPos().X;
	currentPos.Y += gameIntroMenu.getOffsetCenterPos().Y;

	gameIntroMenu.setPos(currentPos);
	ConsoleController::I()->MoveConsolePos(currentPos);

	m_queryLongestMenuInfoCallback(helperTarget, gameIntroMenu);
}

/*
전달받은 메뉴 정보와 비교하면서 가장 긴 메뉴 정보를 알아냅니다.
*/
void GameIntroMenuSceneHelper::OnCallback_QueryLongestMenuInfo(_Inout_ GameIntroMenuScene& helperTarget,
	_Inout_ GameIntroMenu& gameIntroMenu)
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
void GameIntroMenuSceneHelper::OnCallback_NonQueryLongestMenuInfo(_Inout_ GameIntroMenuScene& helperTarget,
	_Inout_ GameIntroMenu& gameIntroMenu)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

EErrorType GameIntroMenuScene::OnInitialize()
{
	InputController::I()->InsertInputMappingInfo("SelectUp", VK_UP);
	InputController::I()->InsertInputMappingInfo("SelectDown", VK_DOWN);
	InputController::I()->InsertInputMappingInfo("SelectMenu", VK_RETURN);

	m_tupleLongestMenuInfo = std::make_tuple("Default", COORD{ SHRT_MIN, SHRT_MIN }, false);

	m_vecGameIntroMenu.push_back(new GameIntroMenu_SceneLoader("배틀 시뮬레이터",
		COORD{ -SCENE_RIGHT_MARGIN_LENGTH, MENU_BATTLE_SIMULATOR_OFFSET_POS_Y }));

	m_vecGameIntroMenu.push_back(new GameIntroMenu_SceneLoader("잡화 상점２",
		COORD{ -SCENE_RIGHT_MARGIN_LENGTH, MENU_MISCELLANEOUS_SHOP2_OFFSET_POS_Y }));

	m_vecGameIntroMenu.push_back(new GameIntroMenu_SceneLoader("다이얼로그 트리",
		COORD{ -SCENE_RIGHT_MARGIN_LENGTH, MENU_DIALOGUE_TREE_OFFSET_POS_Y }));

	m_vecGameIntroMenu.push_back(new GameIntroMenu_Quit("게임 종료",
		COORD{ -SCENE_RIGHT_MARGIN_LENGTH, MENU_QUIT_OFFSET_POS_Y }));

	return EErrorType::NONE;
}

EErrorType GameIntroMenuScene::OnUpdate()
{
	BEGIN_FRAME_UPDDATE_LIMITED();

	if (InputController::I()->CheckInputState("SelectUp", EInputMappingState::PRESSING) == true)
	{
		--m_selectedGameIntroMenuIdx;
		m_selectedGameIntroMenuIdx = CommonFunc::ClampCircular(m_selectedGameIntroMenuIdx, 0, m_vecGameIntroMenu.size() - 1);
		DEBUG_LOG("SelectUp 눌렀다!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::PRESSING) == true)
	{
		++m_selectedGameIntroMenuIdx;
		m_selectedGameIntroMenuIdx = CommonFunc::ClampCircular(m_selectedGameIntroMenuIdx, 0, m_vecGameIntroMenu.size() - 1);
		DEBUG_LOG("SelectDown 눌렀다!");
	}

	if (InputController::I()->CheckInputState("SelectMenu", EInputMappingState::DOWN) == true)
	{
		TriggerTimerMgr::I()->AddTriggerTimer("ExcuteMenu", 3.0f, this, &GameIntroMenuScene::OnTrigger_ExcuteMenu, false);
		DEBUG_LOG("SelectMenu 눌렀다!");
	}

	END_FRAME_UPDATE_LIMITED();
	
	return EErrorType::NONE;
}

EErrorType GameIntroMenuScene::OnRender()
{
	GameIntroMenuSceneHelper::DrawScene(*this);
	return EErrorType::NONE;
}

EErrorType GameIntroMenuScene::OnFinalize()
{
	for (auto& iter : m_vecGameIntroMenu)
	{
		SAFE_DELETE(iter);
	}

	return EErrorType::NONE;
}

void GameIntroMenuScene::OnTrigger_ExcuteMenu()
{
	CHECK_NULLPTR(m_vecGameIntroMenu[m_selectedGameIntroMenuIdx]);
	m_vecGameIntroMenu[m_selectedGameIntroMenuIdx]->OnExcute();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

GameIntroMenu::GameIntroMenu(const std::string_view& szNameTag, const COORD& offsetCenterPos) :
	m_nameTag(szNameTag),
	m_pos{ 0, 0 },
	m_offsetCenterPos(offsetCenterPos)
{
	
}

EErrorType GameIntroMenu::OnExcute()
{
	DEBUG_LOG("GameIntroMenu에서 이게 보이면 OnExcute()를 재정의해주세요!");
	return EErrorType::NONE;
}

EErrorType GameIntroMenu_Quit::OnExcute()
{
	DEBUG_LOG("GameIntroMenuScene에서 게임 종료!");
	GameCtx::I()->setCurrentGameState(EGameState::TERMINATION_SUCCESS);
	return EErrorType::NONE;
}

EErrorType GameIntroMenu_SceneLoader::OnExcute()
{
	// 씬 자체가 타입이므로 여기서는 분기 처리...
	//switch (switch_on)
	//{
	//default:
	//	break;
	//}
	return EErrorType::NONE;
}