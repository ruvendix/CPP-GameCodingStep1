// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ���������� ����ϴ� ķ�ο�ǰ�Դϴ�.
// =====================================================================================

#ifndef SHOP_ITEM_CAMPING_H__
#define SHOP_ITEM_CAMPING_H__

#include "ShopItem.h"

class ShopItem_Camping : public ShopItem
{
public:
#pragma region ������ �� �Ҹ���
	using ShopItem::ShopItem;
	virtual ~ShopItem_Camping() = default;
#pragma endregion
};

#endif