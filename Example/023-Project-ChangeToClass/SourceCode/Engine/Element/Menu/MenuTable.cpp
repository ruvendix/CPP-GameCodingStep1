// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �⺻ �޴� ���̺��Դϴ�.
// �޴��� �߰��ϰ� ������ �� �ֽ�����.
// =====================================================================================

#include "PCH.h"
#include "MenuTable.h"

#include "Controller\InputController.h"
#include "Controller\FrameController.h"
#include "Controller\ConsoleController.h"
#include "Context\ConfigContext.h"
#include "Element\Menu\Menu.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MenuTable::Initialize()
{
	InputController::I()->InsertInputMappingInfo("MenuUp", VK_UP);
	InputController::I()->InsertInputMappingInfo("MenuDown", VK_DOWN);
	InputController::I()->InsertInputMappingInfo("MenuLeft", VK_LEFT);
	InputController::I()->InsertInputMappingInfo("MenuRight", VK_RIGHT);
	InputController::I()->InsertInputMappingInfo("MenuSelect", VK_RETURN);
}

void MenuTable::AddMenu(std::shared_ptr<Menu> spMenu)
{
	m_vecMenu.push_back(spMenu);

	if (m_spLongestMenu == nullptr)
	{
		m_spLongestMenu = spMenu;
	}
	else if (m_spLongestMenu->getNameTag().size() < spMenu->getNameTag().size())
	{
		m_spLongestMenu = spMenu;
	}
}

void MenuTable::AddMenu(std::shared_ptr<Menu> spMenu, Int32 idx)
{
	CHECK_RANGE(idx, 0, m_vecMenu.size() - 1);
	m_vecMenu[idx] = spMenu;
}

void MenuTable::AddCurrentMenuIdx(Int32 value)
{
	m_currentMenuIdx += value;
	m_currentMenuIdx = rx_math::ClampCycle(m_currentMenuIdx, 0, static_cast<Int32>(m_vecMenu.size()) - 1);
}

void MenuTable::ResizeMenuTable(TSize size)
{
	m_vecMenu.resize(size);
}

void MenuTable::AlignCenterForMenu()
{
	for (auto& iter : m_vecMenu)
	{
		CHECK_NULLPTR_CONTINUE(iter);
		ConsoleController::I()->AlignCenter(ConfigCtx::I()->getResoultion(), iter->getSizeInfo());

		// �̵��� �߾� ���� ��ǥ���� �����¸�ŭ �̵�!
		COORD currentPos = ConsoleController::I()->QueryCurrentConsolePos();
		currentPos.X += iter->getOffsetCenterPos().X;
		currentPos.Y += iter->getOffsetCenterPos().Y;

		iter->setPos(currentPos);
		ConsoleController::I()->MoveConsolePos(currentPos);
	}
}

void MenuTable::DrawMenu() const
{
	for (const auto& iter : m_vecMenu)
	{
		CHECK_NULLPTR_CONTINUE(iter);
		const COORD& pos = iter->getPos();
		PUT_STRING(pos.X, pos.Y, "%s", iter->getNameTag().c_str());
	}
}

Int32 MenuTable::ToMenuIdx(const COORD& pos, bool bCenter /* = false */) const
{
	TSize size = m_vecMenu.size();
	for (TSize i = 0; i < size; ++i)
	{
		std::shared_ptr<Menu> spMenu = m_vecMenu.at(i);
		CHECK_NULLPTR_CONTINUE(spMenu);

		Int32 diffPosX = 0;
		const COORD& menuPos = spMenu->getPos();

		if (bCenter == true)
		{
			diffPosX = std::abs(m_spLongestMenu->getPos().X - menuPos.X);
		}

		if ( (menuPos.X == (pos.X + diffPosX)) &&
			 (menuPos.Y == pos.Y) )
		{
			return i;
		}
	}

	return 0;
}

EErrorType MenuTable::ExcuteCurrentMenu()
{
	return getCurrentMenu()->OnExcute();
}
