// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �⺻ �޴� ���̺��Դϴ�.
// �޴��� �߰��ϰ� ������ �� �ֽ�����.
// =====================================================================================

#ifndef MENU_TABLE_H__
#define MENU_TABLE_H__

class Menu;
using MenuPtr = std::shared_ptr<Menu>;

class MenuTable
{
	DECLARE_ROOT_RTTI(MenuTable);

public:
#pragma region ������ �� �Ҹ���
	MenuTable() = default;
	virtual ~MenuTable() = default;
#pragma endregion

	static void Initialize(); // �ѹ��� ȣ���ϸ� ��!

	virtual void OnInput() = 0;

	void AddMenu(MenuPtr spMenu);
	void AddMenu(MenuPtr spMenu, Int32 idx);
	void AddCurrentMenuIdx(Int32 value);
	void ResizeMenuTable(TSize size);
	void AlignCenterForMenu();
	void DrawMenu() const;

	Int32 ToMenuIdx(const COORD& pos, bool bCenter = false) const;
	EErrorType ExcuteCurrentMenu();

	void setCurrentMenuIdx(Int32 menuIdx)
	{
		CHECK_RANGE(menuIdx, 0, m_vecMenu.size() - 1);
		m_currentMenuIdx = menuIdx;
	}

	MenuPtr getMenu(Int32 menuIdx) const
	{
		CHECK_RANGE(menuIdx, 0, m_vecMenu.size() - 1);
		return m_vecMenu.at(menuIdx);
	}

	TSize getMenuCnt() const
	{
		return m_vecMenu.size();
	}

	TSize getLastIdx() const
	{
		return (m_vecMenu.size() - 1);
	}

	MenuPtr getCurrentMenu() const
	{
		return getMenu(m_currentMenuIdx);
	}

	MenuPtr getFirstMenu() const
	{
		return getMenu(0);
	}

	MenuPtr getLastMenu() const
	{
		return getMenu(m_vecMenu.size() - 1);
	}

	MenuPtr getLongestMenu() const
	{
		return m_spLongestMenu;
	}

private:
	Int32 m_currentMenuIdx = 0;
	MenuPtr m_spLongestMenu;
	std::vector<MenuPtr> m_vecMenu;
};

#endif