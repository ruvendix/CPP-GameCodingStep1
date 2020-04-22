// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 시간 관련 함수 모음입니다.
// =====================================================================================

#include "PCH.h"
#include "TimeUtil.h"

/*
타임 포인트를 한국 시간 표현법으로 문자열을 만듭니다.
*/
std::string rx_time::MakeTimeString_HHMMSS(const TimePoint& timePoint)
{
	time_t time = std::chrono::system_clock::to_time_t(timePoint);

	tm timeData;
	::ZeroMemory(&timeData, sizeof(timeData));
	localtime_s(&timeData, &time);

	//DEBUG_LOG("%d년, %d월, %d일, %d시, %d분, %d초",
	//	timeData.tm_year, timeData.tm_mon, timeData.tm_mday, timeData.tm_hour, timeData.tm_min, timeData.tm_sec);

	return common_func::MakeFormatString("%02d시 %02d분 %02d초", timeData.tm_hour, timeData.tm_min, timeData.tm_sec);
}

/*
경과 시간을 시분초로 변환합니다.
디폴트 인자를 이용해도 되지만 의미상 시분초 순서가 되어야 하므로 포인터를 이용합니다.
*/
void rx_time::ToHHMMSS(Real32 elaspedTime, _Out_ Int32* pHour, _Out_ Int32* pMinute, _Out_ Int32* pSecond)
{
	if (pHour != nullptr)
	{
		*pHour = static_cast<Int32>(elaspedTime) / 3600;
	}

	if (pMinute != nullptr)
	{
		*pMinute = static_cast<Int32>(elaspedTime) / 60;
	}

	if (pSecond != nullptr)
	{
		*pSecond = static_cast<Int32>(elaspedTime);
	}
}
