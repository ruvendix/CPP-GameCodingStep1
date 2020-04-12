// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2에서 사용되는 오브젝트 상태 모음입니다.
// =====================================================================================

#ifndef OBJECT_STATE_H__
#define OBJECT_STATE_H__

#include "Common\CommonType.h"

// 상태 패턴 비슷...
enum class EUnitState : Int32
{
	IDLE = 0,
	MOVE,
	ATTACK,
};

#endif