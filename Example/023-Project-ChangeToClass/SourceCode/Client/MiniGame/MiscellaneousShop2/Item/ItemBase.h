// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 아이템 기본형입니다.
// 상점에서만 파는 아이템뿐만 아니라 여러 아이템으로 구현 가능합니다.
// =====================================================================================

#ifndef ITEM_BASE_H__
#define ITEM_BASE_H__

#include "Common\CommonType.h"
#include "Common\CommonMacro.h"
#include "Element\NameTag.h"

class ItemBase
{
	HAS_NAME_TAG();

public:
#pragma region 생성자 및 소멸자
	ItemBase() = default;
	virtual ~ItemBase() = default;
#pragma endregion

	ItemBase* Clone() const;

	Int32 getID() const
	{
		return m_ID;
	}

	Int32 getPrice() const
	{
		return m_price;
	}

	void setID(Int32 ID)
	{
		m_ID = ID;
	}

	void setPrice(Int32 price)
	{
		m_price = price;
	}

private:
	Int32 m_ID = 0;
	Int32 m_price = 0;
};

#endif