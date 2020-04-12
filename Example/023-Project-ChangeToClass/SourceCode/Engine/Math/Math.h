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

	Int32 Clamp(Int32 value, Int32 min, Int32 max);
	Int32 ClampCycle(Int32 value, Int32 min, Int32 max);
	Int32 CalcIdx(Int32 col, Int32 rowIdx, Int32 colIdx);
	
	bool IsValidRange(Int32 value, Int32 min, Int32 max);
	bool IsSamePos(const COORD& srcPos, const COORD& destPos);
	bool IsSamePos(const COORD& srcPos, Int32 destX, Int32 destY);
	bool IsPointInRect(const COORD& targetPos, const COORD& leftTopPos, const COORD& rightBottomPos);

} // namespace math end

#endif