// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 가로로 늘어놓는 메뉴 테이블입니다.
// =====================================================================================

#include "PCH.h"
#include "MenuTable_Col.h"

#include "Controller\ConsoleController.h"
#include "Controller\InputController.h"
#include "Controller\FrameController.h"
#include "Element\Menu\Menu.h"

void MenuTable_Col::OnInput()
{
	if (InputController::I()->CheckInputState("MenuLeft", EInputMappingState::DOWN) == true)
	{
		AddCurrentMenuIdx(-1);
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosX(getCurrentMenu()->getPos().X - ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU);

		m_localTime = 0.0f;
		DEBUG_LOG("MenuLeft 눌렀다!");
	}

	if (InputController::I()->CheckInputState("MenuRight", EInputMappingState::DOWN) == true)
	{
		AddCurrentMenuIdx(+1);
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosX(getCurrentMenu()->getPos().X - ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU);

		m_localTime = 0.0f;
		DEBUG_LOG("MenuRight 눌렀다!");
	}

	BEGIN_INPUT_FPS_LIMITED();
	if (InputController::I()->CheckInputState("MenuLeft", EInputMappingState::PRESSING) == true)
	{
		AddCurrentMenuIdx(-1);
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosX(getCurrentMenu()->getPos().X - ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU);
		DEBUG_LOG("MenuLeft 누르는 중!");
	}

	if (InputController::I()->CheckInputState("MenuRight", EInputMappingState::PRESSING) == true)
	{
		AddCurrentMenuIdx(+1);
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosX(getCurrentMenu()->getPos().X - ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU);
		DEBUG_LOG("MenuRight 누르는 중!");
	}
	END_INPUT_FPS_LIMITED();

	if (InputController::I()->CheckInputState("MenuSelect", EInputMappingState::DOWN) == true)
	{
		ExcuteCurrentMenu();
		DEBUG_LOG("MenuSelect 눌렀다!");
	}
}