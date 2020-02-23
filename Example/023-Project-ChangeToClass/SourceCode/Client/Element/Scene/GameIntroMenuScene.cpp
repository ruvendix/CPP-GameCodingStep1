// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ��Ʈ�� ȭ���� �޴� ���Դϴ�.
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
	static QueryLongestMenuInfoCallback m_queryLongestMenuInfoCallback; // ���� ����
};

// ���� Ŭ������ ��������� �ݹ�� ����� �����Կ�!
// �ٸ� �뵵�� ��������� �ְ� �Ǹ� static�̶� ��� �ν��Ͻ��� �����ع����� ���ؿ�...
GameIntroMenuSceneHelper::QueryLongestMenuInfoCallback GameIntroMenuSceneHelper::m_queryLongestMenuInfoCallback = OnCallback_QueryLongestMenuInfo;

/*
��Ʈ�� ���� �޴� ���� �������մϴ�.
*/
void GameIntroMenuSceneHelper::DrawScene(_Inout_ GameIntroMenuScene& helperTarget)
{
	DrawTitle();
	DrawAllMenu(helperTarget);

	// ���� �� �޴� ������ �˾Ƴ´ٸ� �� �̻� ������Ʈ���� �ʽ��ϴ�!
	if (std::get<2>(helperTarget.m_tupleLongestMenuInfo) == true)
	{
		std::get<2>(helperTarget.m_tupleLongestMenuInfo) = false;
		m_queryLongestMenuInfoCallback = OnCallback_NonQueryLongestMenuInfo;
	}

	DrawSelector(helperTarget);
}

/*
��Ʈ�� ���� �޴� ���� Ÿ��Ʋ�� �������մϴ�.
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
��Ʈ�� ���� �޴� ���� ��� �޴��� �������մϴ�.
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
��Ʈ�� ���� �޴� ���� �����͸� �������մϴ�.
*/
void GameIntroMenuSceneHelper::DrawSelector(const GameIntroMenuScene& helperTarget)
{	
	const std::string_view& strLongestMenuName = std::get<0>(helperTarget.m_tupleLongestMenuInfo);
	const COORD& longestMenuPos = std::get<1>(helperTarget.m_tupleLongestMenuInfo);

	GameIntroMenu* pGameIntroMenu = helperTarget.m_vecGameIntroMenu[helperTarget.m_selectedGameIntroMenuIdx];
	CHECK_NULLPTR(pGameIntroMenu);

	PRINTF(longestMenuPos.X - MENU_MARGIN_LENGTH, pGameIntroMenu->getPos().Y, "��");
	PRINTF(longestMenuPos.X + strLongestMenuName.size() + MENU_MARGIN_LENGTH - 2, pGameIntroMenu->getPos().Y, "��");
}

/*
��Ʈ�� ���� �޴� ���� �޴��� �߾� �����մϴ�.
*/
void GameIntroMenuSceneHelper::AlignCenterMenu(_Inout_ GameIntroMenuScene& helperTarget, _Inout_ GameIntroMenu& gameIntroMenu)
{
	ConsoleController::I()->AlignCenter(ConfigCtx::I()->getResoultion(), gameIntroMenu.getNameTag().size());

	// �̵��� �߾� ���� ��ǥ���� �����¸�ŭ �̵�!
	COORD currentPos = ConsoleController::I()->GetCurrentConsolePos();
	currentPos.X += gameIntroMenu.getOffsetCenterPos().X;
	currentPos.Y += gameIntroMenu.getOffsetCenterPos().Y;

	gameIntroMenu.setPos(currentPos);
	ConsoleController::I()->MoveConsolePos(currentPos);

	m_queryLongestMenuInfoCallback(helperTarget, gameIntroMenu);
}

/*
���޹��� �޴� ������ ���ϸ鼭 ���� �� �޴� ������ �˾Ƴ��ϴ�.
*/
void GameIntroMenuSceneHelper::OnCallback_QueryLongestMenuInfo(_Inout_ GameIntroMenuScene& helperTarget,
	_Inout_ GameIntroMenu& gameIntroMenu)
{
	const COORD& menuPos = gameIntroMenu.getPos();

	Int32 longestMenuPosX = std::get<1>(helperTarget.m_tupleLongestMenuInfo).X;
	if ( (longestMenuPosX == SHRT_MIN) || // ó�� ������ ������ ������!
		 (menuPos.X < longestMenuPosX) )
	{
		std::get<0>(helperTarget.m_tupleLongestMenuInfo) = gameIntroMenu.getNameTag();
		std::get<1>(helperTarget.m_tupleLongestMenuInfo) = menuPos;
	}
}

/*
���� �� �޴� ������ �˾Ƴ� ���̹Ƿ� �ƹ��͵� ���� �ʽ��ϴ�.
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

	m_vecGameIntroMenu.push_back(new GameIntroMenu_SceneLoader("��Ʋ �ùķ�����",
		COORD{ -SCENE_RIGHT_MARGIN_LENGTH, MENU_BATTLE_SIMULATOR_OFFSET_POS_Y }));

	m_vecGameIntroMenu.push_back(new GameIntroMenu_SceneLoader("��ȭ ������",
		COORD{ -SCENE_RIGHT_MARGIN_LENGTH, MENU_MISCELLANEOUS_SHOP2_OFFSET_POS_Y }));

	m_vecGameIntroMenu.push_back(new GameIntroMenu_SceneLoader("���̾�α� Ʈ��",
		COORD{ -SCENE_RIGHT_MARGIN_LENGTH, MENU_DIALOGUE_TREE_OFFSET_POS_Y }));

	m_vecGameIntroMenu.push_back(new GameIntroMenu_Quit("���� ����",
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
		DEBUG_LOG("SelectUp ������!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::PRESSING) == true)
	{
		++m_selectedGameIntroMenuIdx;
		m_selectedGameIntroMenuIdx = CommonFunc::ClampCircular(m_selectedGameIntroMenuIdx, 0, m_vecGameIntroMenu.size() - 1);
		DEBUG_LOG("SelectDown ������!");
	}

	if (InputController::I()->CheckInputState("SelectMenu", EInputMappingState::DOWN) == true)
	{
		TriggerTimerMgr::I()->AddTriggerTimer("ExcuteMenu", 3.0f, this, &GameIntroMenuScene::OnTrigger_ExcuteMenu, false);
		DEBUG_LOG("SelectMenu ������!");
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
	DEBUG_LOG("GameIntroMenu���� �̰� ���̸� OnExcute()�� ���������ּ���!");
	return EErrorType::NONE;
}

EErrorType GameIntroMenu_Quit::OnExcute()
{
	DEBUG_LOG("GameIntroMenuScene���� ���� ����!");
	GameCtx::I()->setCurrentGameState(EGameState::TERMINATION_SUCCESS);
	return EErrorType::NONE;
}

EErrorType GameIntroMenu_SceneLoader::OnExcute()
{
	// �� ��ü�� Ÿ���̹Ƿ� ���⼭�� �б� ó��...
	//switch (switch_on)
	//{
	//default:
	//	break;
	//}
	return EErrorType::NONE;
}