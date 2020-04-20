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

class ItemBase;
class ItemDB;

using ArrItemDB = std::array<ItemDB*, common_func::ToUnderlyingType(EItemDBType::END)>;

class ItemDBCtx final
{
	DECLARE_PHOENIX_SINGLETON(ItemDBCtx);

public:
	void Initialize();
	void Finalize();

	ItemBase* QueryItem(const std::string& strItemNameTag) const;	
	ItemDB* QueryItemDB(EItemDBType itemDBType) const;
	TSize QueryItemCntOfItemDB(EItemDBType itemDBType) const;

private:
	ArrItemDB m_itemDBTable;
};

#endif