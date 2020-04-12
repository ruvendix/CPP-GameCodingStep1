// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ���������� ����ϴ� ȸ�����Դϴ�.
// =====================================================================================

#ifndef SHOP_ITEM_POTION_H__
#define SHOP_ITEM_POTION_H__

#include "ShopItem.h"

class ShopItem_Potion final : public ShopItem
{
	DECLARE_RTTI(ShopItem_Potion, ShopItem);

public:
#pragma region ������ �� �Ҹ���
	using ShopItem::ShopItem;
	virtual ~ShopItem_Potion() = default;
#pragma endregion
};

#endif