// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �������Դϴ�.
// =====================================================================================

#ifndef SHOP_ITEM_H__
#define SHOP_ITEM_H__

#include "../ItemBase.h"

class ShopItem : public ItemBase
{
public:
#pragma region ������ �� �Ҹ���
	using ItemBase::ItemBase;
	virtual ~ShopItem() = default;
#pragma endregion
};

#endif