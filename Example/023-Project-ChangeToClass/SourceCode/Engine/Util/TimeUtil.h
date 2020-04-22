// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 시간 관련 함수 모음입니다.
// =====================================================================================

#ifndef TIME_UTIL__H__
#define TIME_UTIL__H__

#include "Common\CommonType.h"
#include "Common\CommonMacro.h"
#include "Common\CommonNecessary.h"

namespace rx_time
{

	std::string MakeTimeString_HHMMSS(const TimePoint& timePoint);
	void ToHHMMSS(Real32 elaspedTime, _Out_ Int32* pHour, _Out_ Int32* pMinute, _Out_ Int32* pSecond);

} // namespace rx_time end

#endif