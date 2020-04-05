// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 수학 관련 함수 모음입니다.
// =====================================================================================

#include "PCH.h"
#include "Math.h"

namespace math
{

	/*
	숫자를 제한된 범위로 고정시킵니다.
	*/
	Int32 Clamp(Int32 value, Int32 min, Int32 max)
	{
		Int32 retValue = value;

		if (retValue < min)
		{
			retValue = min;
		}
		else if (retValue > max)
		{
			retValue = max;
		}

		return retValue;
	}

	/*
	Clamp()와 비슷하지만 최솟값보다 작아지면 최댓값으로,
	최댓값보다 커지면 최솟값으로 순환되는 버전입니다.
	*/
	Int32 ClampCycle(Int32 value, Int32 min, Int32 max)
	{
		Int32 retValue = value;

		if (retValue < min)
		{
			retValue = max;
		}
		else if (retValue > max)
		{
			retValue = min;
		}

		return retValue;
	}

	Int32 CalcIdx(Int32 col, Int32 rowIdx, Int32 colIdx)
	{
		return ((rowIdx * col) + colIdx);
	}

	bool IsValidRange(Int32 value, Int32 min, Int32 max)
	{
		if ( (value < min) || 
			 (value > max) )
		{
			return false;
		}

		return true;
	}

} // namespace math end