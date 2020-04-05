// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��ȭ����2�� ��ƿ �Լ� �����Դϴ�.
// =====================================================================================

#ifndef MISCELLANEOUS_SHOP2_UTIL_H__
#define MISCELLANEOUS_SHOP2_UTIL_H__

#include "Common\CommonType.h"
#include "Common\CommonMacro.h"
#include "Common\CommonNecessary.h"
#include "Item\ItemDBType.h"

class ItemBase;

class MiscellanouseShop2Util final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(MiscellanouseShop2Util);

public:
	static void DrawItemTable(Int32 x, Int32 y, EItemDBType itemDBType);
};

#endif