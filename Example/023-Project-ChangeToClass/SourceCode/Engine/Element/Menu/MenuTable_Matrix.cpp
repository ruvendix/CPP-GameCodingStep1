// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 가로와 세로로 늘어놓는 메뉴 테이블입니다.
// =====================================================================================

#include "PCH.h"
#include "MenuTable_Matrix.h"

#include "Controller\ConsoleController.h"
#include "Controller\InputController.h"
#include "Controller\FrameController.h"
#include "Element\Menu\Menu.h"

MenuTable_Mat::MenuTable_Mat(Int32 row, Int32 col) :
	m_matInfo{ row, col }
{
	ResizeMenuTable(m_matInfo.row * m_matInfo.col);
}

MenuTable_Mat::MenuTable_Mat(Int32 row, Int32 col, bool bCyclePosX, bool bCyclePosY) :
	MenuTable_Mat(row, col)
{
	m_bCyclePosX = bCyclePosX;
	m_bCyclePosY = bCyclePosY;
}

void MenuTable_Mat::OnInput()
{
	if (InputController::I()->CheckInputState("MenuLeft", EInputMappingState::DOWN) == true)
	{
		--m_currentMatInfo.col;

		if (m_bCyclePosX == true)
		{
			m_currentMatInfo.col = rx_math::ClampCycle(m_currentMatInfo.col, 0, m_matInfo.col - 1);
		}
		else
		{
			m_currentMatInfo.col = rx_math::Clamp(m_currentMatInfo.col, 0, m_matInfo.col - 1);
		}

		ChangeCurrentMenu(rx_math::CalcIdx(m_matInfo.col, m_currentMatInfo.row, m_currentMatInfo.col));
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosX(
			getCurrentMenu()->getPos().X - ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU + ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_BORDER);

		m_localTime = 0.0f;
		DEBUG_LOG("MenuLeft 눌렀다!");
	}

	if (InputController::I()->CheckInputState("MenuRight", EInputMappingState::DOWN) == true)
	{
		++m_currentMatInfo.col;

		if (m_bCyclePosX == true)
		{
			m_currentMatInfo.col = rx_math::ClampCycle(m_currentMatInfo.col, 0, m_matInfo.col - 1);
		}
		else
		{
			m_currentMatInfo.col = rx_math::Clamp(m_currentMatInfo.col, 0, m_matInfo.col - 1);
		}

		ChangeCurrentMenu(rx_math::CalcIdx(m_matInfo.col, m_currentMatInfo.row, m_currentMatInfo.col));
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosX(
			getCurrentMenu()->getPos().X - ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU + ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_BORDER);

		m_localTime = 0.0f;
		DEBUG_LOG("MenuRight 눌렀다!");
	}

	if (InputController::I()->CheckInputState("MenuUp", EInputMappingState::DOWN) == true)
	{
		--m_currentMatInfo.row;

		if (m_bCyclePosY == true)
		{
			m_currentMatInfo.row = rx_math::ClampCycle(m_currentMatInfo.row, 0, m_matInfo.row - 1);
		}
		else
		{
			m_currentMatInfo.row = rx_math::Clamp(m_currentMatInfo.row, 0, m_matInfo.row - 1);
		}

		ChangeCurrentMenu(rx_math::CalcIdx(m_matInfo.col, m_currentMatInfo.row, m_currentMatInfo.col));
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosY(getCurrentMenu()->getPos().Y);

		m_localTime = 0.0f;
		DEBUG_LOG("MenuUp 눌렀다!");
	}

	if (InputController::I()->CheckInputState("MenuDown", EInputMappingState::DOWN) == true)
	{
		++m_currentMatInfo.row;

		if (m_bCyclePosY == true)
		{
			m_currentMatInfo.row = rx_math::ClampCycle(m_currentMatInfo.row, 0, m_matInfo.row - 1);
		}
		else
		{
			m_currentMatInfo.row = rx_math::Clamp(m_currentMatInfo.row, 0, m_matInfo.row - 1);
		}

		ChangeCurrentMenu(rx_math::CalcIdx(m_matInfo.col, m_currentMatInfo.row, m_currentMatInfo.col));
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosY(getCurrentMenu()->getPos().Y);

		m_localTime = 0.0f;
		DEBUG_LOG("MenuDown 눌렀다!");
	}

	BEGIN_INPUT_FPS_LIMITED();
	if (InputController::I()->CheckInputState("MenuLeft", EInputMappingState::PRESSING) == true)
	{
		--m_currentMatInfo.col;

		if (m_bCyclePosX == true)
		{
			m_currentMatInfo.col = rx_math::ClampCycle(m_currentMatInfo.col, 0, m_matInfo.col - 1);
		}
		else
		{
			m_currentMatInfo.col = rx_math::Clamp(m_currentMatInfo.col, 0, m_matInfo.col - 1);
		}

		ChangeCurrentMenu(rx_math::CalcIdx(m_matInfo.col, m_currentMatInfo.row, m_currentMatInfo.col));
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosX(
			getCurrentMenu()->getPos().X - ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU + ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_BORDER);
		DEBUG_LOG("MenuLeft 누르는 중!");
	}

	if (InputController::I()->CheckInputState("MenuRight", EInputMappingState::PRESSING) == true)
	{
		++m_currentMatInfo.col;

		if (m_bCyclePosX == true)
		{
			m_currentMatInfo.col = rx_math::ClampCycle(m_currentMatInfo.col, 0, m_matInfo.col - 1);
		}
		else
		{
			m_currentMatInfo.col = rx_math::Clamp(m_currentMatInfo.col, 0, m_matInfo.col - 1);
		}

		ChangeCurrentMenu(rx_math::CalcIdx(m_matInfo.col, m_currentMatInfo.row, m_currentMatInfo.col));
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosX(
			getCurrentMenu()->getPos().X - ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU + ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_BORDER);
		DEBUG_LOG("MenuRight 누르는 중!");
	}

	if (InputController::I()->CheckInputState("MenuUp", EInputMappingState::PRESSING) == true)
	{
		--m_currentMatInfo.row;

		if (m_bCyclePosY == true)
		{
			m_currentMatInfo.row = rx_math::ClampCycle(m_currentMatInfo.row, 0, m_matInfo.row - 1);
		}
		else
		{
			m_currentMatInfo.row = rx_math::Clamp(m_currentMatInfo.row, 0, m_matInfo.row - 1);
		}

		ChangeCurrentMenu(rx_math::CalcIdx(m_matInfo.col, m_currentMatInfo.row, m_currentMatInfo.col));
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosY(getCurrentMenu()->getPos().Y);
		DEBUG_LOG("MenuUp 누르는 중!");
	}

	if (InputController::I()->CheckInputState("MenuDown", EInputMappingState::PRESSING) == true)
	{
		++m_currentMatInfo.row;

		if (m_bCyclePosY == true)
		{
			m_currentMatInfo.row = rx_math::ClampCycle(m_currentMatInfo.row, 0, m_matInfo.row - 1);
		}
		else
		{
			m_currentMatInfo.row = rx_math::Clamp(m_currentMatInfo.row, 0, m_matInfo.row - 1);
		}

		ChangeCurrentMenu(rx_math::CalcIdx(m_matInfo.col, m_currentMatInfo.row, m_currentMatInfo.col));
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

void MenuTable_Mat::AddMenu(MenuPtr spMenu, Int32 rowIdx, Int32 colIdx)
{
	if ( (m_matInfo.row <= rowIdx) ||
		 (m_matInfo.col <= colIdx) )
	{
		DEFAULT_ERROR_HANDLER(EErrorType::INVALID_MATRIX, rowIdx, colIdx, 0, 0, m_matInfo.row - 1, m_matInfo.col - 1);
		return;
	}

	m_vecMatInfo.push_back(MatInfo{ rowIdx, colIdx });

	Int32 menuIdx = (rowIdx * m_matInfo.col) + colIdx;
	MenuTable::AddMenu(spMenu, menuIdx);
}

void MenuTable_Mat::ChangeCurrentMenu(Int32 menuIdx)
{
	setCurrentMenuIdx(menuIdx);
	
	CHECK_RANGE(menuIdx, 0, m_vecMatInfo.size() - 1);
	m_currentMatInfo = m_vecMatInfo.at(menuIdx);
}
