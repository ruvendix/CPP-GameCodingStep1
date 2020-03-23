// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 아이템 기본형입니다.
// 상점에서만 파는 아이템뿐만 아니라 여러 아이템으로 구현 가능합니다.
// =====================================================================================

#include "PCH.h"
#include "ItemBase.h"

ItemBase* ItemBase::Clone() const
{
	ItemBase* pItem = trace_new ItemBase;
	*pItem = *this;
	return pItem;
}
