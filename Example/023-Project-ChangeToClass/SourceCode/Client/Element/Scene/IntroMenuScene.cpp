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
	
	static void OnCallback_CompMenuInfo_QueryLongest(_Inout_ IntroMenuScene& helperTarget, _Inout_ IntroMenu& gameIntroMenu);
	static void OnCallback_CompMenuInfo_None(_Inout_ IntroMenuScene& helperTarget, _Inout_ IntroMenu& gameIntroMenu);

private:
	static CompMenuInfoCallback m_compMenuInfoCallback; // ���� ����
};

// ���� Ŭ������ ��������� �ݹ�� ����� �����Կ�!
// �ٸ� �뵵�� ��������� �ְ� �Ǹ� static�̶� ��� �ν��Ͻ��� �����ع����� ���ؿ�...
IntroMenuSceneHelper::CompMenuInfoCallback IntroMenuSceneHelper::m_compMenuInfoCallback = OnCallback_CompMenuInfo_QueryLongest;

/*
��Ʈ�� ���� �޴� ���� �������մϴ�.
*/
void IntroMenuSceneHelper::DrawScene(_Inout_ IntroMenuScene& helperTarget)
{
	DrawTitle(helperTarget);
	DrawAllMenu(helperTarget);

	// ���� �� �޴� ������ �˾Ƴ´ٸ� �� �̻� ������Ʈ���� �ʽ��ϴ�!
	if (std::get<2>(helperTarget.m_tupleLongestMenuInfo) == true)
	{
		std::get<2>(helperTarget.m_tupleLongestMenuInfo) = false;
		m_compMenuInfoCallback = OnCallback_CompMenuInfo_None;
	}

	DrawSelector(helperTarget);
}

/*
��Ʈ�� ���� �޴� ���� Ÿ��Ʋ�� �������մϴ�.
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
��Ʈ�� ���� �޴� ���� ��� �޴��� �������մϴ�.
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

		COORD currentConsolePos = ConsoleController::I()->GetCurrentConsolePos();
		PRINTF(currentConsolePos.X, currentConsolePos.Y, "%s", iter->getNameTag().c_str());
	}
}

/*
��Ʈ�� ���� �޴� ���� �����͸� �������մϴ�.
*/
void IntroMenuSceneHelper::DrawSelector(const IntroMenuScene& helperTarget)
{	
	const std::string_view& strLongestMenuName = std::get<0>(helperTarget.m_tupleLongestMenuInfo);
	const COORD& longestMenuPos = std::get<1>(helperTarget.m_tupleLongestMenuInfo);

	IntroMenu* pGameIntroMenu = helperTarget.m_vecIntroMenu[helperTarget.m_selectedIntroMenuIdx];
	CHECK_NULLPTR(pGameIntroMenu);

	PRINTF(longestMenuPos.X - MENU_MARGIN_LENGTH, pGameIntroMenu->getPos().Y, "��");
	PRINTF(longestMenuPos.X + strLongestMenuName.size() + MENU_MARGIN_LENGTH - 2, pGameIntroMenu->getPos().Y, "��");
}

/*
��Ʈ�� ���� �޴� ���� �޴��� �߾� �����մϴ�.
*/
void IntroMenuSceneHelper::AlignCenterMenu(_Inout_ IntroMenuScene& helperTarget, _Inout_ IntroMenu& gameIntroMenu)
{
	ConsoleController::I()->AlignCenter(ConfigCtx::I()->getResoultion(), gameIntroMenu.getNameTag().size());

	// �̵��� �߾� ���� ��ǥ���� �����¸�ŭ �̵�!
	COORD currentPos = ConsoleController::I()->GetCurrentConsolePos();
	currentPos.X += gameIntroMenu.getOffsetCenterPos().X;
	currentPos.Y += gameIntroMenu.getOffsetCenterPos().Y;

	gameIntroMenu.setPos(currentPos);
	ConsoleController::I()->MoveConsolePos(currentPos);

	m_compMenuInfoCallback(helperTarget, gameIntroMenu);
}

/*
���޹��� �޴� ������ ���ϸ鼭 ���� �� �޴� ������ �˾Ƴ��ϴ�.
*/
void IntroMenuSceneHelper::OnCallback_CompMenuInfo_QueryLongest(_Inout_ IntroMenuScene& helperTarget, _Inout_ IntroMenu& gameIntroMenu)
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
void IntroMenuSceneHelper::OnCallback_CompMenuInfo_None(_Inout_ IntroMenuScene& helperTarget, _Inout_ IntroMenu& gameIntroMenu)
{

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

	m_vecIntroMenu.push_back(trace_new IntroMenu_SceneLoader("��Ʋ �ùķ�����",
		COORD{ -SCENE_RIGHT_MARGIN_LENGTH, MENU_BATTLE_SIMULATOR_OFFSET_POS_Y }, EIntroMenu_SceneLoaderType::BATTLE_SIMULATOR));

	m_vecIntroMenu.push_back(trace_new IntroMenu_SceneLoader("��ȭ ������",
		COORD{ -SCENE_RIGHT_MARGIN_LENGTH, MENU_MISCELLANEOUS_SHOP2_OFFSET_POS_Y }, EIntroMenu_SceneLoaderType::MISCELLANEOUS_SHOP2));

	m_vecIntroMenu.push_back(trace_new IntroMenu_SceneLoader("���̾�α� Ʈ��",
		COORD{ -SCENE_RIGHT_MARGIN_LENGTH, MENU_DIALOGUE_TREE_OFFSET_POS_Y }, EIntroMenu_SceneLoaderType::DIALOGUE_TREE));

	m_vecIntroMenu.push_back(trace_new IntroMenu_Quit("���� ����", COORD{ -SCENE_RIGHT_MARGIN_LENGTH, MENU_QUIT_OFFSET_POS_Y }));

	TriggerTimerMgr::I()->AddTriggerTimer("ChangeIntroTitle", 0.3f, 0.0f, this, &IntroMenuScene::OnTrigger_ChangeRandomColorToTitle, false, true);

	return EErrorType::NONE;
}

EErrorType IntroMenuScene::OnUpdate()
{
	if (InputController::I()->CheckInputState("SelectUp", EInputMappingState::DOWN) == true)
	{
		--m_selectedIntroMenuIdx;
		m_selectedIntroMenuIdx = math::ClampCycle(m_selectedIntroMenuIdx, 0, m_vecIntroMenu.size() - 1);
		m_localTime = 0.0f;
		DEBUG_LOG_CATEGORY(IntroMenuScene, "SelectUp ������!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::DOWN) == true)
	{
		++m_selectedIntroMenuIdx;
		m_selectedIntroMenuIdx = math::ClampCycle(m_selectedIntroMenuIdx, 0, m_vecIntroMenu.size() - 1);
		m_localTime = 0.0f;
		DEBUG_LOG_CATEGORY(IntroMenuScene, "SelectDown ������!");
	}

	BEGIN_FRAME_UPDATE_LIMITED();
	if (InputController::I()->CheckInputState("SelectUp", EInputMappingState::PRESSING) == true)
	{
		--m_selectedIntroMenuIdx;
		m_selectedIntroMenuIdx = math::ClampCycle(m_selectedIntroMenuIdx, 0, m_vecIntroMenu.size() - 1);
		DEBUG_LOG_CATEGORY(IntroMenuScene, "SelectUp ������ ��!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::PRESSING) == true)
	{
		++m_selectedIntroMenuIdx;
		m_selectedIntroMenuIdx = math::ClampCycle(m_selectedIntroMenuIdx, 0, m_vecIntroMenu.size() - 1);
		DEBUG_LOG_CATEGORY(IntroMenuScene, "SelectDown ������ ��!");
	}
	END_FRAME_UPDATE_LIMITED();

	if (InputController::I()->CheckInputState("SelectMenu", EInputMappingState::DOWN) == true)
	{
		TriggerTimerMgr::I()->AddTriggerTimer("ExcuteMenu", 1.0f, 0.0f, this, &IntroMenuScene::OnTrigger_ExcuteMenu, false, false);
		DEBUG_LOG_CATEGORY(IntroMenuScene, "SelectMenu ������!");
	}

	if (InputController::I()->CheckInputState("Exit", EInputMappingState::DOWN) == true)
	{
		m_vecIntroMenu[static_cast<Int32>(m_vecIntroMenu.size() - 1)]->OnExcute();
		DEBUG_LOG_CATEGORY(IntroMenuScene, "Exit ������!");
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
	for (auto& iter : m_vecIntroMenu)
	{
		SAFE_DELETE(iter);
	}

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