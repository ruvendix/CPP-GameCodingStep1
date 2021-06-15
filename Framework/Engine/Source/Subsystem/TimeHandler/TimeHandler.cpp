// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 타임 핸들러의 인터페이스입니다.
// 외부 데이터와 함수를 갖고 있으니 추상 클래스이기도 합니다.
// 시간 변환 등 시간 관련 내용을 다룹니다.
// =====================================================================================
#include "EnginePCH.h"
#include "TimeHandler.h"

#include "TimeData.h"

void TimeHandler::SetUp()
{
	TimeData::TimeOption& timeOption = Data()->GetTimeOption();
	timeOption.set(EnumIdx::TimeOption::YEAR, true);
	timeOption.set(EnumIdx::TimeOption::MONTH, true);
	timeOption.set(EnumIdx::TimeOption::DAY, true);
	timeOption.set(EnumIdx::TimeOption::HOUR, true);
	timeOption.set(EnumIdx::TimeOption::MINUTE, true);
	timeOption.set(EnumIdx::TimeOption::SECOND, true);

	TimeData::TimeOrders& timeOrders = Data()->GetTimeOrders();
	timeOrders[0] = EnumIdx::TimeOption::YEAR;
	timeOrders[1] = EnumIdx::TimeOption::MONTH;
	timeOrders[2] = EnumIdx::TimeOption::DAY;
	timeOrders[3] = EnumIdx::TimeOption::HOUR;
	timeOrders[4] = EnumIdx::TimeOption::MINUTE;
	timeOrders[5] = EnumIdx::TimeOption::SECOND;
}

void TimeHandler::CleanUp()
{

}

Uint32 TimeHandler::ConvertSecondsToMinutes(Float seconds) const
{
	return static_cast<Uint32>(seconds / 60.0f);
}

Uint32 TimeHandler::ConvertSecondsToHours(Float seconds) const
{
	return static_cast<Uint32>(seconds / 3600.0f);
}

void TimeHandler::MakeLocalTimeString(OUT std::string& strLocalTime, Char delimiter)
{
	std::time_t currentTime;
	std::time(&currentTime);
	std::tm* pCurrentTime = std::localtime(&currentTime);
	RX_SIMPLE_ASSERT(pCurrentTime != nullptr);

	TimeData::TimeOption& timeOption = Data()->GetTimeOption();
	std::array<std::string, EnumIdx::TimeOption::COUNT> strElems;

	// 각 시간 요소 넣기
	{
		if (timeOption.test(EnumIdx::TimeOption::YEAR) == true)
		{
			strElems[EnumIdx::TimeOption::YEAR] = std::to_string(pCurrentTime->tm_year + 1900);
		}

		if (timeOption.test(EnumIdx::TimeOption::MONTH) == true)
		{
			strElems[EnumIdx::TimeOption::MONTH] = std::to_string(pCurrentTime->tm_mon + 1);
		}

		if (timeOption.test(EnumIdx::TimeOption::DAY) == true)
		{
			strElems[EnumIdx::TimeOption::DAY] = std::to_string(pCurrentTime->tm_mday);
		}

		if (timeOption.test(EnumIdx::TimeOption::HOUR) == true)
		{
			strElems[EnumIdx::TimeOption::HOUR] = std::to_string(pCurrentTime->tm_hour);
		}

		if (timeOption.test(EnumIdx::TimeOption::MINUTE) == true)
		{
			strElems[EnumIdx::TimeOption::MINUTE] = std::to_string(pCurrentTime->tm_min);
		}

		if (timeOption.test(EnumIdx::TimeOption::SECOND) == true)
		{
			strElems[EnumIdx::TimeOption::SECOND] = std::to_string(pCurrentTime->tm_sec);
		}
	}

	TimeData::TimeOrders& timeOrders = Data()->GetTimeOrders();

	// 각 시간 요소 순서 정하기
	{
		for (Uint32 i = 0; i < EnumIdx::TimeOption::COUNT; ++i)
		{
			EnumIdx::TimeOption::Data timeOrder = timeOrders[i];
			if (strElems[timeOrder].empty() == true) // 해당 시간 요소가 없음
			{
				continue;
			}

			strLocalTime += strElems[timeOrder];
			strElems[timeOrder].clear();

			if (i != EnumIdx::TimeOption::COUNT - 1)
			{
				strLocalTime += delimiter;
			}
		}
	}
}
