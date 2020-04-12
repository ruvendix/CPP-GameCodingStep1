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

enum class EStaticObjID : Int32
{
	UNKNOWN = 0,
	WALL,
	END, // 동적 오브젝트 ID와의 경계용으로 사용!
};

enum class EDynamicObjID : Int32
{
	UNKNOWN = static_cast<Int32>(EStaticObjID::END),
	VIKING,
	MEDIEVAL_KNIGHT
};

#endif