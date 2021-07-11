// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 컴포넌트에 사용되는 열거형입니다.
// 각 컴포넌트를 구분할 때 사용됩니다.
// =====================================================================================
#pragma once

#include "Common/CommonType.h"

enum class EComponentType : Int32
{
	UNKNOWN = -1,
	TRANSFORM,
	MOVE,
	COUNT,
};