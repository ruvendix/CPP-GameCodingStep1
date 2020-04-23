// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 아이템 DB 모음입니다.
// 아이템 조회할 때 이용하면 됩니다.
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