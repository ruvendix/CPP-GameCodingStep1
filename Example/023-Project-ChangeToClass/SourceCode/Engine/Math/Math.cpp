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
		Int32 resultValue = value;

		if (resultValue < min)
		{
			resultValue = min;
		}
		else if (resultValue > max)
		{
			resultValue = max;
		}

		return resultValue;
	}

	/*
	Clamp()�� ��������� �ּڰ����� �۾����� �ִ�����,
	�ִ񰪺��� Ŀ���� �ּڰ����� ��ȯ�Ǵ� �����Դϴ�.
	*/
	Int32 ClampCycle(Int32 value, Int32 min, Int32 max)
	{
		Int32 resultValue = value;

		if (resultValue < min)
		{
			resultValue = max;
		}
		else if (resultValue > max)
		{
			resultValue = min;
		}

		return resultValue;
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