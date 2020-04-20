// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���η� �þ���� �޴� ���̺��Դϴ�.
// =====================================================================================

#ifndef MENU_TABLE_COL_H__
#define MENU_TABLE_COL_H__

#include "MenuTable.h"

class MenuTable_Col : public MenuTable
{
	DECLARE_RTTI(MenuTable_Col, MenuTable);
	INPUT_FPS_LIMITED(8);

public:
#pragma region ������ �� �Ҹ���
	using MenuTable::MenuTable;
	virtual ~MenuTable_Col() = default;
#pragma endregion

	virtual void OnInput() override;
};

#endif