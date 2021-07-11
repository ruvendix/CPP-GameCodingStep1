// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 타임 핸들러에 사용되는 열거형입니다.
// =====================================================================================
#pragma once

#include "Common/CommonType.h"

// 변환용으로만 사용됩니다.
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
		// SYSTEMTIME과 순서 동일합니다.
		enum Data
		{
			UNKNOWN = -1,
			YEAR,
			MONTH, // 1월(1)부터 12월(12)까지
			DAY_OF_WEEK, // 일요일(0)부터 토요일(6)까지
			DAY,
			HOUR,
			MINUTE,
			SECOND,
			MILLISECOND,
			COUNT,
		};
	}
}