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

#include "Base/TimeData.h"
#include "Core/Graph/GraphInclusion.h"

const TimeHandler::ConvertionTimeTable TimeHandler::UPPER_CONVERTION_TIME_TABLE =
{
	1.0f / 1000.0f,
	1.0f / 60.0f,
	1.0f / 60.0f,
	1.0f / 24.0f,
	1.0f / 365.0f,
};

const TimeHandler::ConvertionTimeTable TimeHandler::LOWER_CONVERTION_TIME_TABLE =
{
	1000.0f,
	60.0f,
	60.0f,
	24.0f,
	365.0f,
};

TimeHandler::TimeHandler()
{
	
}

void TimeHandler::SetUp()
{
	TimeData::TimeOrders& timeOrders = Data()->GetTimeOrders();
	for (Uint32 i = 0; i < EnumIdx::TimeUnit::COUNT; ++i)
	{
		EnumIdx::TimeUnit::Data timeUnit = static_cast<EnumIdx::TimeUnit::Data>(i);
		ActivateTimeUnit(timeUnit);

		timeOrders[i] = timeUnit;
	}
}

void TimeHandler::CleanUp()
{

}

Float TimeHandler::ConvertTime(Float time, EConvertionTimeUnit src, EConvertionTimeUnit dest) const
{
	if (src == dest)
	{
		return time;
	}

	Int32 currentStep = ToUnderlyingType(src);
	Int32 diff = currentStep - ToUnderlyingType(dest);

	Uint32 diffStep = std::abs(diff);
	Bool bSign = std::signbit(static_cast<Float>(diff)); // 음수면 true, 양수면 false

	// 높은 단위 -> 낮은 단위
	if (bSign == false)
	{
		Int32 startStep = currentStep - 1;
		for (Uint32 i = 0; i < diffStep; ++i)
		{
			time *= TimeHandler::LOWER_CONVERTION_TIME_TABLE[startStep - i];
		}
	}
	// 낮은 단위 -> 높은 단위
	else
	{
		Int32 startStep = currentStep;
		for (Uint32 i = 0; i < diffStep; ++i)
		{
			time *= TimeHandler::UPPER_CONVERTION_TIME_TABLE[startStep + i];
		}
	}

	return time;
}

void TimeHandler::MakeLocalTimeString(OUT std::string& strLocalTime, Char delimiter)
{
	SYSTEMTIME systemTime;
	::GetLocalTime(&systemTime);

	constexpr Uint32 timeUnitCount = EnumIdx::TimeUnit::COUNT;
	std::array<WORD, timeUnitCount> localTime =
	{
		systemTime.wYear,
		systemTime.wMonth,
		systemTime.wDayOfWeek,
		systemTime.wDay,
		systemTime.wHour,
		systemTime.wMinute,
		systemTime.wSecond,
		systemTime.wMilliseconds
	};

	std::array<std::string, 7> strDayOfWeek =
	{
		"일", "월", "화", "수", "목", "금", "토"
	};
	
	std::array<std::string, timeUnitCount> strTimeUnits;

	// 각 시간 단위 넣기
	for (Uint32 i = 0; i < timeUnitCount; ++i)
	{
		EnumIdx::TimeUnit::Data timeUnit = static_cast<EnumIdx::TimeUnit::Data>(i);
		if (CheckTimeUnit(timeUnit) == false)
		{
			continue;
		}

		if (timeUnit == EnumIdx::TimeUnit::DAY_OF_WEEK)
		{
			strTimeUnits[timeUnit] = strDayOfWeek[localTime[timeUnit]];
		}
		else
		{
			strTimeUnits[i] = std::to_string(localTime[i]);
		}
	}

	strLocalTime.clear();

	// 각 시간 단위의 표시 순서 정하기
	TimeData::TimeOrders& timeOrders = Data()->GetTimeOrders();
	for (Uint32 i = 0; i < timeUnitCount; ++i)
	{
		EnumIdx::TimeUnit::Data orderIdx = timeOrders[i];

		const std::string& strTimeUnit = strTimeUnits[orderIdx];
		if (strTimeUnit.empty() == true) // 해당 시간 단위를 사용하지 않겠다는 의미
		{
			continue;
		}

		strLocalTime += strTimeUnit;
		strLocalTime += delimiter;
	}

	// delimiter 제거
	strLocalTime.pop_back();
}

void TimeHandler::ActivateTimeUnit(EnumIdx::TimeUnit::Data timeUnit)
{
	Data()->GetTimeUnits().set(timeUnit, true);
}

void TimeHandler::DeactivateTimeUnit(EnumIdx::TimeUnit::Data timeUnit)
{
	Data()->GetTimeUnits().set(timeUnit, false);
}

bool TimeHandler::CheckTimeUnit(EnumIdx::TimeUnit::Data timeUnit) const
{
	return Data()->GetTimeUnits().test(ToUnderlyingType(timeUnit));
}

void TimeHandler::ChangeTimeOrder(EnumIdx::TimeUnit::Data timeUnit, Uint32 orderIdx)
{
	TimeData::TimeOrders& timeOrders = Data()->GetTimeOrders();

	Int32 prevIdx = -1;
	for (Uint32 i = 0; i < EnumIdx::TimeUnit::COUNT; ++i)
	{
		if (timeOrders[i] == timeUnit)
		{
			prevIdx = i;
			break;
		}
	}

	// 이전 시간 단위와 현재 시간 단위가 같다면 변경하는 의미가 없습니다.
	EnumIdx::TimeUnit::Data prevTimeUnit = timeOrders[orderIdx];
	if (prevTimeUnit == timeUnit)
	{
		return;
	}

	// 현재 넣을 인덱스와 값 교체
	timeOrders[orderIdx] = timeUnit;
	timeOrders[prevIdx] = prevTimeUnit;
}