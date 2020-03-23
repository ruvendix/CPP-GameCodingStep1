// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 아이템 DB 타입 모음입니다.
// =====================================================================================

#ifndef ITEM_DB_ENUM_H__
#define ITEM_DB_ENUM_H__

#include "Common\CommonType.h"

enum class EItemDBType : Int32
{
	NONE = -1,
	POTION,
	GROCERY,
	CAMPING,
	END,
};

#endif