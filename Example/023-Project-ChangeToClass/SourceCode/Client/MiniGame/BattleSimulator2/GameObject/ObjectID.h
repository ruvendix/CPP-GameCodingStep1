// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2에서 사용되는 오브젝트 ID 모음입니다.
// 정적 오브젝트와 동적 오브젝트 둘 다 포함됩니다.
// =====================================================================================

#ifndef OBJECT_ID_H__
#define OBJECT_ID_H__

#include "Common\CommonType.h"

enum class EObjID : Int32
{
	UNKNOWN = 0,

	START_STATIC_OBJ_ID,
	WALL,
	END_STATIC_OBJ_ID,

	START_DYNAMIC_OBJ_ID,
	VIKING,
	MEDIEVAL_KNIGHT,
	END_DYNAMIC_OBJ_ID,
};

#endif