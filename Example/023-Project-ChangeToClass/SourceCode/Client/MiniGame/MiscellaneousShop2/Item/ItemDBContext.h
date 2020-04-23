// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������ DB �����Դϴ�.
// ������ ��ȸ�� �� �̿��ϸ� �˴ϴ�.
// =====================================================================================

#ifndef ITEM_DB_CONTEXT_H__
#define ITEM_DB_CONTEXT_H__

#include "Common\CommonFunc.h"
#include "ItemDBType.h"

class ItemDB;
class ItemBase;

using ItemDBPtr = std::shared_ptr<ItemDB>;
using ItemBasePtr = std::shared_ptr<ItemBase>;
using ArrItemDB = std::array<ItemDBPtr, common_func::ToUnderlyingType(EItemDBType::END)>;

class ItemDBCtx final
{
	DECLARE_PHOENIX_SINGLETON(ItemDBCtx);

public:
	void Initialize();

	ItemBasePtr FindItem(const std::string& strItemNameTag) const;
	ItemDBPtr FindItemDB(EItemDBType type) const;
	TSize FindItemCntOfItemDB(EItemDBType type) const;

private:
	ArrItemDB m_arrItemDB;
};

#endif