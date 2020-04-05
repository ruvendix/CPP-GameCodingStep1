// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���η� �þ���� �޴� ���̺��Դϴ�.
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
		DEBUG_LOG("MenuUp ������!");
	}

	if (InputController::I()->CheckInputState("MenuDown", EInputMappingState::DOWN) == true)
	{
		AddCurrentMenuIdx(+1);
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosY(getCurrentMenu()->getPos().Y);

		m_localTime = 0.0f;
		DEBUG_LOG("MenuDown ������!");
	}

	BEGIN_INPUT_FPS_LIMITED();
	if (InputController::I()->CheckInputState("MenuUp", EInputMappingState::PRESSING) == true)
	{
		AddCurrentMenuIdx(-1);
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosY(getCurrentMenu()->getPos().Y);
		DEBUG_LOG("MenuUp ������ ��!");
	}

	if (InputController::I()->CheckInputState("MenuDown", EInputMappingState::PRESSING) == true)
	{
		AddCurrentMenuIdx(+1);
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosY(getCurrentMenu()->getPos().Y);
		DEBUG_LOG("MenuDown ������ ��!");
	}
	END_INPUT_FPS_LIMITED();

	if (InputController::I()->CheckInputState("MenuSelect", EInputMappingState::DOWN) == true)
	{
		ExcuteCurrentMenu();		
		DEBUG_LOG("MenuSelect ������!");
	}
}