// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���ο� ���η� �þ���� �޴� ���̺��Դϴ�.
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

#pragma region ������ �� �Ҹ���
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