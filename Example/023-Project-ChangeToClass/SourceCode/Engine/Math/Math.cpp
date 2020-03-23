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
	Int32 Clamp(Int32 val, Int32 minVal, Int32 maxVal)
	{
		Int32 resultVal = val;

		if (resultVal < minVal)
		{
			resultVal = minVal;
		}
		else if (resultVal > maxVal)
		{
			resultVal = maxVal;
		}

		return resultVal;
	}

	/*
	Clamp()�� ��������� �ּڰ����� �۾����� �ִ�����,
	�ִ񰪺��� Ŀ���� �ּڰ����� ��ȯ�Ǵ� �����Դϴ�.
	*/
	Int32 ClampCycle(Int32 val, Int32 minVal, Int32 maxVal)
	{
		Int32 resultVal = val;

		if (resultVal < minVal)
		{
			resultVal = maxVal;
		}
		else if (resultVal > maxVal)
		{
			resultVal = minVal;
		}

		return resultVal;
	}

} // namespace math end