// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 아이템 DB 모음입니다.
// 아이템 조회할 때 이용하면 됩니다.
// =====================================================================================

#include "PCH.h"
#include "ItemDBContext.h"

#include "ItemDB.h"
#include "ShopItem\ShopItem_Potion.h"
#include "ShopItem\ShopItem_Grocery.h"
#include "ShopItem\ShopItem_Camping.h"

DEFINE_PHOENIX_SINGLETON(ItemDBCtx);

void ItemDBCtx::Initialize()
{
	// 포션 DB 초기화
	ItemDB* pPotionDB = new ItemDB;
	pPotionDB->InsertItem<ShopItem_Potion>("평범한 회복약", 0x00001000, 10);
	pPotionDB->InsertItem<ShopItem_Potion>("쓸만한 회복약", 0x00001001, 50);
	pPotionDB->InsertItem<ShopItem_Potion>("특제 회복약", 0x00001002, 100);
	pPotionDB->InsertItem<ShopItem_Potion>("만병통치약", 0x00001003, 200);
	m_itemDBTable[common_func::ToUnderlyingType(EItemDBType::POTION)] = pPotionDB;

	// 식료품 DB 초기화
	ItemDB* pGroceryDB = new ItemDB;
	pGroceryDB->InsertItem<ShopItem_Grocery>("계란", 0x00002000, 5);
	pGroceryDB->InsertItem<ShopItem_Grocery>("돼지고기", 0x00002001, 10);
	pGroceryDB->InsertItem<ShopItem_Grocery>("소고기", 0x00002002, 20);
	pGroceryDB->InsertItem<ShopItem_Grocery>("소금", 0x00002003, 5);
	pGroceryDB->InsertItem<ShopItem_Grocery>("후추", 0x00002004, 5);
	m_itemDBTable[common_func::ToUnderlyingType(EItemDBType::GROCERY)] = pGroceryDB;

	// 캠핑용품
	ItemDB* pCampingDB = new ItemDB;
	pCampingDB->InsertItem<ShopItem_Camping>("야영텐트", 0x00003000, 150);
	pCampingDB->InsertItem<ShopItem_Camping>("가스 토치", 0x00003001, 100);
	pCampingDB->InsertItem<ShopItem_Camping>("손전등", 0x00003002, 50);
	pCampingDB->InsertItem<ShopItem_Camping>("침낭", 0x00003003, 150);
	m_itemDBTable[common_func::ToUnderlyingType(EItemDBType::CAMPING)] = pCampingDB;
}

void ItemDBCtx::Finalize()
{
	for (auto& iter : m_itemDBTable)
	{
		SAFE_DELETE(iter);
	}
}

ItemBase* ItemDBCtx::QueryItem(const std::string& strItemNameTag) const
{
	for (const auto& iter : m_itemDBTable)
	{
		CHECK_NULLPTR(iter);
		return (iter->FindItem(strItemNameTag));
	}

	return nullptr;
}

ItemDB* ItemDBCtx::QueryItemDB(EItemDBType itemDBType) const
{
	return m_itemDBTable.at(common_func::ToUnderlyingType(itemDBType));
}

TSize ItemDBCtx::QueryItemCntOfItemDB(EItemDBType itemDBType) const
{
	ItemDB* pItemDB = QueryItemDB(itemDBType);
	if (pItemDB == nullptr)
	{
		return 0;
	}

	return (pItemDB->getMapItemDB().size());
}
