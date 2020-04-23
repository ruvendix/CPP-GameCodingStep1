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
	ItemDBPtr spPotionDB = std::make_shared<ItemDB>();
	spPotionDB->InsertItem<ShopItem_Potion>("평범한 회복약", 0x00001000, 10);
	spPotionDB->InsertItem<ShopItem_Potion>("쓸만한 회복약", 0x00001001, 50);
	spPotionDB->InsertItem<ShopItem_Potion>("특제 회복약", 0x00001002, 100);
	spPotionDB->InsertItem<ShopItem_Potion>("만병통치약", 0x00001003, 200);
	m_arrItemDB[common_func::ToUnderlyingType(EItemDBType::POTION)] = spPotionDB;

	// 식료품 DB 초기화
	ItemDBPtr spGroceryDB = std::make_shared<ItemDB>();
	spGroceryDB->InsertItem<ShopItem_Grocery>("계란", 0x00002000, 5);
	spGroceryDB->InsertItem<ShopItem_Grocery>("돼지고기", 0x00002001, 10);
	spGroceryDB->InsertItem<ShopItem_Grocery>("소고기", 0x00002002, 20);
	spGroceryDB->InsertItem<ShopItem_Grocery>("소금", 0x00002003, 5);
	spGroceryDB->InsertItem<ShopItem_Grocery>("후추", 0x00002004, 5);
	m_arrItemDB[common_func::ToUnderlyingType(EItemDBType::GROCERY)] = spGroceryDB;

	// 캠핑용품
	ItemDBPtr spCampingDB = std::make_shared<ItemDB>();
	spCampingDB->InsertItem<ShopItem_Camping>("야영텐트", 0x00003000, 150);
	spCampingDB->InsertItem<ShopItem_Camping>("가스 토치", 0x00003001, 100);
	spCampingDB->InsertItem<ShopItem_Camping>("손전등", 0x00003002, 50);
	spCampingDB->InsertItem<ShopItem_Camping>("침낭", 0x00003003, 150);
	m_arrItemDB[common_func::ToUnderlyingType(EItemDBType::CAMPING)] = spCampingDB;
}

ItemBasePtr ItemDBCtx::FindItem(const std::string& strItemNameTag) const
{
	for (const auto& iter : m_arrItemDB)
	{
		CHECK_NULLPTR(iter);
		return (iter->FindItem(strItemNameTag));
	}

	return nullptr;
}

ItemDBPtr ItemDBCtx::FindItemDB(EItemDBType type) const
{
	return m_arrItemDB.at(common_func::ToUnderlyingType(type));
}

TSize ItemDBCtx::FindItemCntOfItemDB(EItemDBType type) const
{
	ItemDBPtr spItemDB = FindItemDB(type);
	return (spItemDB->getMapItemDB().Size());
}
