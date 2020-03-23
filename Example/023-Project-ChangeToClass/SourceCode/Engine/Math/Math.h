// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 수학 관련 함수 모음입니다.
// =====================================================================================

#ifndef MATH__H__
#define MATH__H__

#include "Common\CommonType.h"
#include "Common\CommonMacro.h"
#include "Common\CommonNecessary.h"

namespace math
{

	Int32 Clamp(Int32 val, Int32 minVal, Int32 maxVal);
	Int32 ClampCycle(Int32 val, Int32 minVal, Int32 maxVal);

} // namespace math end

#endif