// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 게임 인트로 화면의 메뉴 씬입니다.
// =====================================================================================

#include "PCH.h"
#include "GameIntroMenu.h"

#include "Context\ConfigContext.h"
#include "Context\GameContext.h"
#include "Manager\SceneManager.h"
#include "Controller\InputController.h"

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
	using QueryLongestMenuInfoFunc = std::function<void(_Inout_ GameIntroMenuScene&, _Inout_ GameIntroMenu&)>;

	static void DrawScene(_Inout_ GameIntroMenuScene& helperTarget);
	static void DrawTitle();
	static void DrawAllMenu(_Inout_ GameIntroMenuScene& helperTarget);
	static void DrawSelector(const GameIntroMenuScene& helperTarget);
	static void AlignCenterMenu(_Inout_ GameIntroMenuScene& helperTarget, _Inout_ GameIntroMenu& gameIntroMenu);
	
	static void OnCallback_QueryLongestMenuInfo(_Inout_ GameIntroMenuScene& helperTarget, _Inout_ GameIntroMenu& gameIntroMenu);
	static void OnCallback_NonQueryLongestMenuInfo(_Inout_ GameIntroMenuScene& helperTarget, _Inout_ GameIntroMenu& gameIntroMenu);

private:
	static QueryLongestMenuInfoFunc m_queryLongestMenuInfoFunc; // 전략 패턴
};

// 헬퍼 클래스의 멤버변수는 콜백만 넣을게요!
// 다른 용도의 멤버변수를 넣게 되면 static이라 모든 인스턴스가 공유해버려서 망해요...
GameIntroMenuSceneHelper::QueryLongestMenuInfoFunc GameIntroMenuSceneHelper::m_queryLongestMenuInfoFunc = OnCallback_QueryLongestMenuInfo;

void GameIntroMenuSceneHelper::DrawScene(_Inout_ GameIntroMenuScene& helperTarget)
{
	DrawTitle();
	DrawAllMenu(helperTarget);

	// 가장 긴 메뉴 정보를 알아냈다면 더 이상 업데이트하지 않습니다!
	if (std::get<2>(helperTarget.m_tupleLongestMenuInfo) == true)
	{
		std::get<2>(helperTarget.m_tupleLongestMenuInfo) = false;
		m_queryLongestMenuInfoFunc = OnCallback_NonQueryLongestMenuInfo;
	}

	DrawSelector(helperTarget);
}

void GameIntroMenuSceneHelper::DrawTitle()
{
	printf("   _______  __   __  _______  __    _  _______  _______    _______  _______    _______  ___      _______  _______  _______ \n");
	printf("  |       ||  | |  ||   _   ||  |  | ||       ||       |  |       ||       |  |       ||   |    |   _   ||       ||       |\n");
	printf("  |       ||  |_|  ||  |_|  ||   |_| ||    ___||    ___|  |_     _||   _   |  |       ||   |    |  |_|  ||  _____||  _____|\n");
	printf("  |     __||       ||       ||       ||   | __ |   |___     |   |  |  | |  |  |     __||   |    |       || |_____ | |_____ \n");
	printf("  |    |__ |       ||       ||  _    ||   ||  ||    ___|    |   |  |  |_|  |  |    |__ |   |___ |       ||_____  ||_____  |\n");
	printf("  |       ||   _   ||   _   || | |   ||   |_| ||   |___     |   |  |       |  |       ||       ||   _   | _____| | _____| |\n");
	printf("  |_______||__| |__||__| |__||_|  |__||_______||_______|    |___|  |_______|  |_______||_______||__| |__||_______||_______|\n");
}

void GameIntroMenuSceneHelper::DrawAllMenu(_Inout_ GameIntroMenuScene& helperTarget)
{
	for (auto& iter : helperTarget.m_vecGameIntroMenu)
	{
		if (iter == nullptr)
		{
			continue;
		}

		AlignCenterMenu(helperTarget, *iter);
		printf("%s", iter->getNameTag().c_str());
	}
}

void GameIntroMenuSceneHelper::DrawSelector(const GameIntroMenuScene& helperTarget)
{	
	const std::string_view& strLongestMenuName = std::get<0>(helperTarget.m_tupleLongestMenuInfo);
	const COORD& longestMenuPos = std::get<1>(helperTarget.m_tupleLongestMenuInfo);

	GameIntroMenu* pGameIntroMenu = helperTarget.m_vecGameIntroMenu[helperTarget.m_selectedGameIntroMenuIdx];
	CHECK_NULLPTR(pGameIntroMenu);

	CommonFunc::MoveConsolePos(longestMenuPos.X - MENU_MARGIN_LENGTH, pGameIntroMenu->getPos().Y);
	printf("◀");

	CommonFunc::MoveConsolePos(longestMenuPos.X + strLongestMenuName.size() + MENU_MARGIN_LENGTH - 2, pGameIntroMenu->getPos().Y);
	printf("▶");
}

void GameIntroMenuSceneHelper::AlignCenterMenu(_Inout_ GameIntroMenuScene& helperTarget, _Inout_ GameIntroMenu& gameIntroMenu)
{
	CommonFunc::AlignCenterToConsole(ConfigCtx::I()->getResoultion(), gameIntroMenu.getNameTag().size());

	// 이동된 중앙 정렬 좌표에서 오프셋만큼 이동!
	COORD currentPos = CommonFunc::GetCurrentConsolePos();
	currentPos.X += gameIntroMenu.getOffsetCenterPos().X;
	currentPos.Y += gameIntroMenu.getOffsetCenterPos().Y;

	gameIntroMenu.setPos(currentPos);
	CommonFunc::MoveConsolePos(currentPos);

	m_queryLongestMenuInfoFunc(helperTarget, gameIntroMenu);
}

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

	if (InputController::I()->CheckInputState("SelectMenu", EInputMappingState::PRESSING) == true)
	{
		CHECK_NULLPTR(m_vecGameIntroMenu[m_selectedGameIntroMenuIdx]);
		m_vecGameIntroMenu[m_selectedGameIntroMenuIdx]->OnExcute();
		DEBUG_LOG("SelectMenu 눌렀다!");
	}

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