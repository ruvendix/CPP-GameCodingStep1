// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���η� �þ���� �޴� ���̺��Դϴ�.
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
		DEBUG_LOG("MenuLeft ������!");
	}

	if (InputController::I()->CheckInputState("MenuRight", EInputMappingState::DOWN) == true)
	{
		AddCurrentMenuIdx(+1);
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosX(getCurrentMenu()->getPos().X - ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU);

		m_localTime = 0.0f;
		DEBUG_LOG("MenuRight ������!");
	}

	BEGIN_INPUT_FPS_LIMITED();
	if (InputController::I()->CheckInputState("MenuLeft", EInputMappingState::PRESSING) == true)
	{
		AddCurrentMenuIdx(-1);
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosX(getCurrentMenu()->getPos().X - ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU);
		DEBUG_LOG("MenuLeft ������ ��!");
	}

	if (InputController::I()->CheckInputState("MenuRight", EInputMappingState::PRESSING) == true)
	{
		AddCurrentMenuIdx(+1);
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosX(getCurrentMenu()->getPos().X - ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU);
		DEBUG_LOG("MenuRight ������ ��!");
	}
	END_INPUT_FPS_LIMITED();

	if (InputController::I()->CheckInputState("MenuSelect", EInputMappingState::DOWN) == true)
	{
		ExcuteCurrentMenu();
		DEBUG_LOG("MenuSelect ������!");
	}
}