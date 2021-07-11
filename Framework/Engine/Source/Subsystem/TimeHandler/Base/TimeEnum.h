// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Ÿ�� �ڵ鷯�� ���Ǵ� �������Դϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonType.h"

// ��ȯ�����θ� ���˴ϴ�.
enum class EConvertionTimeUnit : Int32
{
	UNKNOWN = -1,
	MILLISECOND,
	SECOND,
	MINUTE,
	HOUR,
	DAY,
	YEAR,
	COUNT,
};

namespace EnumIdx
{
	namespace TimeUnit
	{
		// SYSTEMTIME�� ���� �����մϴ�.
		enum Data
		{
			UNKNOWN = -1,
			YEAR,
			MONTH, // 1��(1)���� 12��(12)����
			DAY_OF_WEEK, // �Ͽ���(0)���� �����(6)����
			DAY,
			HOUR,
			MINUTE,
			SECOND,
			MILLISECOND,
			COUNT,
		};
	}
}