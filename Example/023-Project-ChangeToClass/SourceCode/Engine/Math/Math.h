// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ���� �Լ� �����Դϴ�.
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