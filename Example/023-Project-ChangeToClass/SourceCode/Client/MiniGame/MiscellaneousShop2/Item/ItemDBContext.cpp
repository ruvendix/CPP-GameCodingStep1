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
	ItemDB* pPotionDB = new ItemDB;
	pPotionDB->InsertItem<ShopItem_Potion>("����� ȸ����", 0x00001000, 10);
	pPotionDB->InsertItem<ShopItem_Potion>("������ ȸ����", 0x00001001, 50);
	pPotionDB->InsertItem<ShopItem_Potion>("Ư�� ȸ����", 0x00001002, 100);
	pPotionDB->InsertItem<ShopItem_Potion>("������ġ��", 0x00001003, 200);
	m_itemDBTable[common_func::ToUnderlyingType(EItemDBType::POTION)] = pPotionDB;

	// �ķ�ǰ DB �ʱ�ȭ
	ItemDB* pGroceryDB = new ItemDB;
	pGroceryDB->InsertItem<ShopItem_Grocery>("���", 0x00002000, 5);
	pGroceryDB->InsertItem<ShopItem_Grocery>("�������", 0x00002001, 10);
	pGroceryDB->InsertItem<ShopItem_Grocery>("�Ұ��", 0x00002002, 20);
	pGroceryDB->InsertItem<ShopItem_Grocery>("�ұ�", 0x00002003, 5);
	pGroceryDB->InsertItem<ShopItem_Grocery>("����", 0x00002004, 5);
	m_itemDBTable[common_func::ToUnderlyingType(EItemDBType::GROCERY)] = pGroceryDB;

	// ķ�ο�ǰ
	ItemDB* pCampingDB = new ItemDB;
	pCampingDB->InsertItem<ShopItem_Camping>("�߿���Ʈ", 0x00003000, 150);
	pCampingDB->InsertItem<ShopItem_Camping>("���� ��ġ", 0x00003001, 100);
	pCampingDB->InsertItem<ShopItem_Camping>("������", 0x00003002, 50);
	pCampingDB->InsertItem<ShopItem_Camping>("ħ��", 0x00003003, 150);
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
