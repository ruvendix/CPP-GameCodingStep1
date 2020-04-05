// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 세로로 늘어놓는 메뉴 테이블입니다.
// =====================================================================================

#include "PCH.h"
#include "MenuTable_Row.h"


#include "Controller\ConsoleController.h"
#include "Controller\InputController.h"
#include "Controller\FrameController.h"
#include "Element\Menu\Menu.h"

void MenuTable_Row::OnInput()
{
	if (InputController::I()->CheckInputState("MenuUp", EInputMappingState::DOWN) == true)
	{
		AddCurrentMenuIdx(-1);
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosY(getCurrentMenu()->getPos().Y);

		m_localTime = 0.0f;
		DEBUG_LOG("MenuUp 눌렀다!");
	}

	if (InputController::I()->CheckInputState("MenuDown", EInputMappingState::DOWN) == true)
	{
		AddCurrentMenuIdx(+1);
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosY(getCurrentMenu()->getPos().Y);

		m_localTime = 0.0f;
		DEBUG_LOG("MenuDown 눌렀다!");
	}

	BEGIN_INPUT_FPS_LIMITED();
	if (InputController::I()->CheckInputState("MenuUp", EInputMappingState::PRESSING) == true)
	{
		AddCurrentMenuIdx(-1);
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosY(getCurrentMenu()->getPos().Y);
		DEBUG_LOG("MenuUp 누르는 중!");
	}

	if (InputController::I()->CheckInputState("MenuDown", EInputMappingState::PRESSING) == true)
	{
		AddCurrentMenuIdx(+1);
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosY(getCurrentMenu()->getPos().Y);
		DEBUG_LOG("MenuDown 누르는 중!");
	}
	END_INPUT_FPS_LIMITED();

	if (InputController::I()->CheckInputState("MenuSelect", EInputMappingState::DOWN) == true)
	{
		ExcuteCurrentMenu();		
		DEBUG_LOG("MenuSelect 눌렀다!");
	}
}