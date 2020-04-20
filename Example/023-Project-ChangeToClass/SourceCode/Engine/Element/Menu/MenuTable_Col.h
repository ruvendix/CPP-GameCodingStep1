// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 가로로 늘어놓는 메뉴 테이블입니다.
// =====================================================================================

#ifndef MENU_TABLE_COL_H__
#define MENU_TABLE_COL_H__

#include "MenuTable.h"

class MenuTable_Col : public MenuTable
{
	DECLARE_RTTI(MenuTable_Col, MenuTable);
	INPUT_FPS_LIMITED(8);

public:
#pragma region 생성자 및 소멸자
	using MenuTable::MenuTable;
	virtual ~MenuTable_Col() = default;
#pragma endregion

	virtual void OnInput() override;
};

#endif