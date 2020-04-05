// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���ο� ���η� �þ���� �޴� ���̺��Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "MenuTable_Matrix.h"

#include "Controller\ConsoleController.h"
#include "Controller\InputController.h"
#include "Controller\FrameController.h"
#include "Element\Menu\Menu.h"

MenuTable_Mat::MenuTable_Mat(Int32 row, Int32 col) :
	m_row(row),
	m_col(col)
{
	ResizeMenuTable(m_row * m_col);
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
		--m_currentColIdx;

		if (m_bCyclePosX == true)
		{
			m_currentColIdx = math::ClampCycle(m_currentColIdx, 0, m_col - 1);
		}
		else
		{
			m_currentColIdx = math::Clamp(m_currentColIdx, 0, m_col - 1);
		}

		setCurrentMenuIdx(math::CalcIdx(m_col, m_currentRowIdx, m_currentColIdx));
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosX(
			getCurrentMenu()->getPos().X - ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU + ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_BORDER);

		m_localTime = 0.0f;
		DEBUG_LOG("MenuLeft ������!");
	}

	if (InputController::I()->CheckInputState("MenuRight", EInputMappingState::DOWN) == true)
	{
		++m_currentColIdx;

		if (m_bCyclePosX == true)
		{
			m_currentColIdx = math::ClampCycle(m_currentColIdx, 0, m_col - 1);
		}
		else
		{
			m_currentColIdx = math::Clamp(m_currentColIdx, 0, m_col - 1);
		}

		setCurrentMenuIdx(math::CalcIdx(m_col, m_currentRowIdx, m_currentColIdx));
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosX(
			getCurrentMenu()->getPos().X - ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU + ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_BORDER);

		m_localTime = 0.0f;
		DEBUG_LOG("MenuRight ������!");
	}

	if (InputController::I()->CheckInputState("MenuUp", EInputMappingState::DOWN) == true)
	{
		--m_currentRowIdx;

		if (m_bCyclePosY == true)
		{
			m_currentRowIdx = math::ClampCycle(m_currentRowIdx, 0, m_row - 1);
		}
		else
		{
			m_currentRowIdx = math::Clamp(m_currentRowIdx, 0, m_row - 1);
		}

		setCurrentMenuIdx(math::CalcIdx(m_col, m_currentRowIdx, m_currentColIdx));
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosY(getCurrentMenu()->getPos().Y);

		m_localTime = 0.0f;
		DEBUG_LOG("MenuUp ������!");
	}

	if (InputController::I()->CheckInputState("MenuDown", EInputMappingState::DOWN) == true)
	{
		++m_currentRowIdx;

		if (m_bCyclePosY == true)
		{
			m_currentRowIdx = math::ClampCycle(m_currentRowIdx, 0, m_row - 1);
		}
		else
		{
			m_currentRowIdx = math::Clamp(m_currentRowIdx, 0, m_row - 1);
		}

		setCurrentMenuIdx(math::CalcIdx(m_col, m_currentRowIdx, m_currentColIdx));
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosY(getCurrentMenu()->getPos().Y);

		m_localTime = 0.0f;
		DEBUG_LOG("MenuDown ������!");
	}

	BEGIN_INPUT_FPS_LIMITED();
	if (InputController::I()->CheckInputState("MenuLeft", EInputMappingState::PRESSING) == true)
	{
		--m_currentColIdx;

		if (m_bCyclePosX == true)
		{
			m_currentColIdx = math::ClampCycle(m_currentColIdx, 0, m_col - 1);
		}
		else
		{
			m_currentColIdx = math::Clamp(m_currentColIdx, 0, m_col - 1);
		}

		setCurrentMenuIdx(math::CalcIdx(m_col, m_currentRowIdx, m_currentColIdx));
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosX(
			getCurrentMenu()->getPos().X - ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU + ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_BORDER);
		DEBUG_LOG("MenuLeft ������ ��!");
	}

	if (InputController::I()->CheckInputState("MenuRight", EInputMappingState::PRESSING) == true)
	{
		++m_currentColIdx;
		
		if (m_bCyclePosX == true)
		{
			m_currentColIdx = math::ClampCycle(m_currentColIdx, 0, m_col - 1);
		}
		else
		{
			m_currentColIdx = math::Clamp(m_currentColIdx, 0, m_col - 1);
		}

		setCurrentMenuIdx(math::CalcIdx(m_col, m_currentRowIdx, m_currentColIdx));
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosX(
			getCurrentMenu()->getPos().X - ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU + ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_BORDER);
		DEBUG_LOG("MenuRight ������ ��!");
	}

	if (InputController::I()->CheckInputState("MenuUp", EInputMappingState::PRESSING) == true)
	{
		--m_currentRowIdx;

		if (m_bCyclePosY == true)
		{
			m_currentRowIdx = math::ClampCycle(m_currentRowIdx, 0, m_row - 1);
		}
		else
		{
			m_currentRowIdx = math::Clamp(m_currentRowIdx, 0, m_row - 1);
		}

		setCurrentMenuIdx(math::CalcIdx(m_col, m_currentRowIdx, m_currentColIdx));
		ConsoleController::I()->ModifyCurrentConsoleSelectorPosY(getCurrentMenu()->getPos().Y);
		DEBUG_LOG("MenuUp ������ ��!");
	}

	if (InputController::I()->CheckInputState("MenuDown", EInputMappingState::PRESSING) == true)
	{
		++m_currentRowIdx;

		if (m_bCyclePosY == true)
		{
			m_currentRowIdx = math::ClampCycle(m_currentRowIdx, 0, m_row - 1);
		}
		else
		{
			m_currentRowIdx = math::Clamp(m_currentRowIdx, 0, m_row - 1);
		}

		setCurrentMenuIdx(math::CalcIdx(m_col, m_currentRowIdx, m_currentColIdx));
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

void MenuTable_Mat::AddForMat(std::shared_ptr<Menu> spMenu, Int32 rowIdx, Int32 colIdx)
{
	if ( (m_row <= rowIdx) ||
		 (m_col <= colIdx) )
	{
		DEFAULT_ERROR_HANDLER(EErrorType::INVALID_MATRIX, rowIdx, colIdx, m_row, m_col, 0, 0, m_row - 1, m_col - 1);
		return;
	}

	Int32 menuIdx = (rowIdx * m_col) + colIdx;
	AddMenu(spMenu, menuIdx);
}
