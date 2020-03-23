// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 상점 아이템입니다.
// =====================================================================================

#ifndef SHOP_ITEM_H__
#define SHOP_ITEM_H__

#include "../ItemBase.h"

class ShopItem : public ItemBase
{
public:
#pragma region 생성자 및 소멸자
	using ItemBase::ItemBase;
	virtual ~ShopItem() = default;
#pragma endregion
};

#endif