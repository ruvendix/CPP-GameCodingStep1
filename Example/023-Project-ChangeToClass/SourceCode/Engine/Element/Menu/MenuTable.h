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

	void AddMenu(std::shared_ptr<Menu> spMenu);
	void AddMenu(std::shared_ptr<Menu> spMenu, Int32 idx);
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

	std::shared_ptr<Menu> getMenu(Int32 menuIdx) const
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

	std::shared_ptr<Menu> getCurrentMenu() const
	{
		return getMenu(m_currentMenuIdx);
	}

	std::shared_ptr<Menu> getFirstMenu() const
	{
		return getMenu(0);
	}

	std::shared_ptr<Menu> getLastMenu() const
	{
		return getMenu(m_vecMenu.size() - 1);
	}

	std::shared_ptr<Menu> getLongestMenu() const
	{
		return m_spLongestMenu;
	}

private:
	Int32 m_currentMenuIdx = 0;
	std::shared_ptr<Menu> m_spLongestMenu;
	std::vector<std::shared_ptr<Menu>> m_vecMenu;
};

#endif