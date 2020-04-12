// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 가로와 세로로 늘어놓는 메뉴 테이블입니다.
// =====================================================================================

#ifndef MENU_TABLE_MAT_H__
#define MENU_TABLE_MAT_H__

#include "MenuTable.h"

class MenuTable_Mat : public MenuTable
{
	DECLARE_RTTI(MenuTable_Mat, MenuTable);
	INPUT_FPS_LIMITED(8);

public:
	using MenuTable::MenuTable;

#pragma region 생성자 및 소멸자
	MenuTable_Mat() = default;
	virtual ~MenuTable_Mat() = default;

	MenuTable_Mat(Int32 row, Int32 col);
	MenuTable_Mat(Int32 row, Int32 col, bool bCyclePosX, bool bCyclePosY);
#pragma endregion

	virtual void OnInput() override;

	void AddForMat(std::shared_ptr<Menu> spMenu, Int32 rowIdx, Int32 colIdx);

private:
	Int32 m_row = 0;
	Int32 m_col = 0;

	Int32 m_currentRowIdx = 0;
	Int32 m_currentColIdx = 0;

	bool m_bCyclePosX = true;
	bool m_bCyclePosY = true;
};

#endif