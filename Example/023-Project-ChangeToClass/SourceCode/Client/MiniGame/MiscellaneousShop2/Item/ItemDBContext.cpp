// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������ DB �����Դϴ�.
// ������ ��ȸ�� �� �̿��ϸ� �˴ϴ�.
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
	// ���� DB �ʱ�ȭ
	ItemDBPtr spPotionDB = std::make_shared<ItemDB>();
	spPotionDB->InsertItem<ShopItem_Potion>("����� ȸ����", 0x00001000, 10);
	spPotionDB->InsertItem<ShopItem_Potion>("������ ȸ����", 0x00001001, 50);
	spPotionDB->InsertItem<ShopItem_Potion>("Ư�� ȸ����", 0x00001002, 100);
	spPotionDB->InsertItem<ShopItem_Potion>("������ġ��", 0x00001003, 200);
	m_arrItemDB[common_func::ToUnderlyingType(EItemDBType::POTION)] = spPotionDB;

	// �ķ�ǰ DB �ʱ�ȭ
	ItemDBPtr spGroceryDB = std::make_shared<ItemDB>();
	spGroceryDB->InsertItem<ShopItem_Grocery>("���", 0x00002000, 5);
	spGroceryDB->InsertItem<ShopItem_Grocery>("�������", 0x00002001, 10);
	spGroceryDB->InsertItem<ShopItem_Grocery>("�Ұ��", 0x00002002, 20);
	spGroceryDB->InsertItem<ShopItem_Grocery>("�ұ�", 0x00002003, 5);
	spGroceryDB->InsertItem<ShopItem_Grocery>("����", 0x00002004, 5);
	m_arrItemDB[common_func::ToUnderlyingType(EItemDBType::GROCERY)] = spGroceryDB;

	// ķ�ο�ǰ
	ItemDBPtr spCampingDB = std::make_shared<ItemDB>();
	spCampingDB->InsertItem<ShopItem_Camping>("�߿���Ʈ", 0x00003000, 150);
	spCampingDB->InsertItem<ShopItem_Camping>("���� ��ġ", 0x00003001, 100);
	spCampingDB->InsertItem<ShopItem_Camping>("������", 0x00003002, 50);
	spCampingDB->InsertItem<ShopItem_Camping>("ħ��", 0x00003003, 150);
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
