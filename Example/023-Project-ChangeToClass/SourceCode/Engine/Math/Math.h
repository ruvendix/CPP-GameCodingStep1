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

} // namespace math end

#endif