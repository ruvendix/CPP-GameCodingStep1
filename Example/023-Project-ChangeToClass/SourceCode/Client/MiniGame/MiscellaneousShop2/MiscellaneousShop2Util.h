// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 잡화상점2의 유틸 함수 모음입니다.
// =====================================================================================

#ifndef MISCELLANEOUS_SHOP2_UTIL_H__
#define MISCELLANEOUS_SHOP2_UTIL_H__

#include "Common\CommonType.h"
#include "Common\CommonMacro.h"
#include "Common\CommonNecessary.h"
#include "Item\ItemDBType.h"

class ItemBase;

class MiscellanouseShop2Util final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(MiscellanouseShop2Util);

public:
	static void DrawItemTable(Int32 x, Int32 y, EItemDBType itemDBType);
};

#endif