// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ��Ʈ�� ȭ���� �޴� ���Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "GameIntroMenu.h"

#include "Context\ConfigContext.h"
#include "Controller\InputController.h"

namespace
{
	const Int32 SCENE_RIGHT_MARGIN_LENGTH = 2;
	const Int32 MENU_MARGIN_LENGTH = 4;
	const Int32 MENU_BATTLE_SIMULATOR_OFFSET_POS_X = 0;
	const Int32 MENU_MISCELLANEOUS_SHOP2_OFFSET_POS_X = MENU_BATTLE_SIMULATOR_OFFSET_POS_X - 2;
	const Int32 MENU_DIALOGUE_TREE_OFFSET_POS_X = MENU_MISCELLANEOUS_SHOP2_OFFSET_POS_X - 2;
	const Int32 MENU_GAME_EXIT_OFFSET_POS_X = MENU_DIALOGUE_TREE_OFFSET_POS_X - 2;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameIntroMenuSceneHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(GameIntroMenuSceneHelper);

public:
	using TupleCompMenuInfo = std::tuple<std::string, COORD, bool>;
	using QueryLongestMenuInfoFunc = std::function<void(const std::string_view&, const COORD&)>;

	static void DrawScene();
	static void DrawTitle();
	static void DrawAllMenu();
	static void AlignCenterMenu(const std::string_view& szMenu, Int32 offsetPosX, Int32 offsetPosY);
	
	static void QueryLongestMenuInfo(const std::string_view& szMenuName, const COORD& menuPos);
	static void NonQueryLongestMenuInfo(const std::string_view& szMenuName, const COORD& menuPos);

private:
	static TupleCompMenuInfo m_tupleLongestMenuInfo;
	static std::function<void(const std::string_view&, const COORD&)> m_queryLongestMenuInfoCallback; // ���� ����
};

GameIntroMenuSceneHelper::TupleCompMenuInfo GameIntroMenuSceneHelper::m_tupleLongestMenuInfo = std::make_tuple("Default", COORD{ SHRT_MIN, SHRT_MIN }, true);
GameIntroMenuSceneHelper::QueryLongestMenuInfoFunc GameIntroMenuSceneHelper::m_queryLongestMenuInfoCallback = QueryLongestMenuInfo;

void GameIntroMenuSceneHelper::DrawScene()
{
	DrawTitle();
	DrawAllMenu();

	// Ʃ���� ��ҷ� ����!
	std::string strLongestMenuInfo;
	COORD longestMenuMenuPos;
	bool bQueryLongestMenuInfo;
	std::tie(strLongestMenuInfo, longestMenuMenuPos, bQueryLongestMenuInfo) = m_tupleLongestMenuInfo;

	// ���� �� �޴� ������ �˾Ƴ´ٸ� �� �̻� ������Ʈ���� �ʽ��ϴ�!
	if (bQueryLongestMenuInfo == true)
	{
		std::get<2>(m_tupleLongestMenuInfo) = false;
		m_queryLongestMenuInfoCallback = NonQueryLongestMenuInfo;
	}

	// �׽�Ʈ
	CommonFunc::MoveConsolePos(longestMenuMenuPos.X - MENU_MARGIN_LENGTH, longestMenuMenuPos.Y);
	printf("��");
	CommonFunc::MoveConsolePos(longestMenuMenuPos.X + strLongestMenuInfo.size() + MENU_MARGIN_LENGTH - 2, longestMenuMenuPos.Y);
	printf("��");
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

void GameIntroMenuSceneHelper::DrawAllMenu()
{
	std::string strMenuName = "��Ʋ �ùķ�����";
	AlignCenterMenu(strMenuName, -SCENE_RIGHT_MARGIN_LENGTH, -MENU_BATTLE_SIMULATOR_OFFSET_POS_X);
	printf("%s", strMenuName.c_str());

	strMenuName = "��ȭ ������";
	AlignCenterMenu(strMenuName, -SCENE_RIGHT_MARGIN_LENGTH, -MENU_MISCELLANEOUS_SHOP2_OFFSET_POS_X);
	printf("%s", strMenuName.c_str());

	strMenuName = "���̾�α� Ʈ��";
	AlignCenterMenu(strMenuName, -SCENE_RIGHT_MARGIN_LENGTH, -MENU_DIALOGUE_TREE_OFFSET_POS_X);
	printf("%s", strMenuName.c_str());

	strMenuName = "���� ����";
	AlignCenterMenu(strMenuName, -SCENE_RIGHT_MARGIN_LENGTH, -MENU_GAME_EXIT_OFFSET_POS_X);
	printf("%s", strMenuName.c_str());
}

void GameIntroMenuSceneHelper::AlignCenterMenu(const std::string_view& szMenu, Int32 offsetPosX, Int32 offsetPosY)
{
	CommonFunc::AlignCenterToConsole(ConfigCtx::I()->getResoultion(), szMenu.size());

	// �̵��� �߾� ���� ��ǥ���� �����¸�ŭ �̵�!
	COORD currentPos = CommonFunc::GetCurrentConsolePos();
	currentPos.X += offsetPosX;
	currentPos.Y += offsetPosY;

	CommonFunc::MoveConsolePos(currentPos);

	m_queryLongestMenuInfoCallback(szMenu, currentPos);
}

void GameIntroMenuSceneHelper::QueryLongestMenuInfo(const std::string_view& szMenuName, const COORD& menuPos)
{
	Int32 longestMenuPosX = std::get<1>(m_tupleLongestMenuInfo).X;
	if ( (longestMenuPosX == SHRT_MIN) || // ó�� ������ ������ ������!
		 (menuPos.X <longestMenuPosX) )
	{
		std::get<0>(m_tupleLongestMenuInfo) = szMenuName;
		std::get<1>(m_tupleLongestMenuInfo) = menuPos;
	}
}

void GameIntroMenuSceneHelper::NonQueryLongestMenuInfo(const std::string_view& szMenuName, const COORD& menuPosX)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

EErrorType GameIntroMenuScene::OnInitialize()
{
	InputController::I()->InsertInputMappingInfo("TestAction", 'C', 'D', VK_UP, 'A');

	return EErrorType::NONE;
}

EErrorType GameIntroMenuScene::OnUpdate()
{
	if (InputController::I()->CheckInputState("TestAction", EInputMappingState::PRESSING) == true)
	{
		DEBUG_LOG("TestAction ������!");
	}

	return EErrorType::NONE;
}

EErrorType GameIntroMenuScene::OnRender()
{
	GameIntroMenuSceneHelper::DrawScene();
	return EErrorType::NONE;
}

EErrorType GameIntroMenuScene::OnFinalize()
{
	return EErrorType::NONE;
}
