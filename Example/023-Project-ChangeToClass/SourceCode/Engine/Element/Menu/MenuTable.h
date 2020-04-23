// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 기본 메뉴 테이블입니다.
// 메뉴를 추가하고 실행할 수 있습닏나.
// =====================================================================================

#ifndef MENU_TABLE_H__
#define MENU_TABLE_H__

class Menu;
using MenuPtr = std::shared_ptr<Menu>;

class MenuTable
{
	DECLARE_ROOT_RTTI(MenuTable);

public:
#pragma region 생성자 및 소멸자
	MenuTable() = default;
	virtual ~MenuTable() = default;
#pragma endregion

	static void Initialize(); // 한번만 호출하면 됨!

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