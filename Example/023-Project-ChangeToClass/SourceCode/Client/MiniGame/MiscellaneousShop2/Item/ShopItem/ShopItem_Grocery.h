// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ���������� ����ϴ� �ķ�ǰ�Դϴ�.
// =====================================================================================

#ifndef SHOP_ITEM_GROCERY_H__
#define SHOP_ITEM_GROCERY_H__

#include "ShopItem.h"

class ShopItem_Grocery final : public ShopItem
{
	DECLARE_RTTI(ShopItem_Grocery, ShopItem);

public:
#pragma region ������ �� �Ҹ���
	using ShopItem::ShopItem;
	virtual ~ShopItem_Grocery() = default;
#pragma endregion
};

#endif