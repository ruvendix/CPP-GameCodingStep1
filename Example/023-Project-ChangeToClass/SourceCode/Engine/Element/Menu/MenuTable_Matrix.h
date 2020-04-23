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

struct MatInfo
{
	Int32 row = 0;
	Int32 col = 0;
};

class MenuTable_Mat : public MenuTable
{
	DECLARE_RTTI(MenuTable_Mat, MenuTable);
	INPUT_FPS_LIMITED(8);

public:
#pragma region ������ �� �Ҹ���
	using MenuTable::MenuTable;

	MenuTable_Mat() = default;
	virtual ~MenuTable_Mat() = default;

	MenuTable_Mat(Int32 row, Int32 col);
	MenuTable_Mat(Int32 row, Int32 col, bool bCyclePosX, bool bCyclePosY);
#pragma endregion

	virtual void OnInput() override;

	void AddMenu(MenuPtr spMenu, Int32 rowIdx, Int32 colIdx);
	void ChangeCurrentMenu(Int32 menuIdx);

private:
	MatInfo m_matInfo;
	MatInfo m_currentMatInfo;
	std::vector<MatInfo> m_vecMatInfo;

	bool m_bCyclePosX = true;
	bool m_bCyclePosY = true;
};

#endif