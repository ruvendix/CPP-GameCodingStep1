// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ���� �Լ� �����Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "Math.h"

namespace math
{

	/*
	���ڸ� ���ѵ� ������ ������ŵ�ϴ�.
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
	Clamp()�� ��������� �ּڰ����� �۾����� �ִ�����,
	�ִ񰪺��� Ŀ���� �ּڰ����� ��ȯ�Ǵ� �����Դϴ�.
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