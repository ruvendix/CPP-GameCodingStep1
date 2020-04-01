// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 게임 오브젝트 타입 모음입니다.
// 엔진에서 사용하는 기반 게임 오브젝트 타입만 있습니다.
// =====================================================================================

#ifndef GAME_OBJ_TYPE__H__
#define GAME_OBJ_TYPE__H__

#include "Common\CommonType.h"

enum class EGameObjType : Int32
{
	NONE = 0,
	STATIC,
	DYNAMIC,
};

#endif