// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Ÿ�� �ڵ鷯�� �������̽��Դϴ�.
// �ܺ� �����Ϳ� �Լ��� ���� ������ �߻� Ŭ�����̱⵵ �մϴ�.
// �ð� ��ȯ �� �ð� ���� ������ �ٷ�ϴ�.
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
	Bool bSign = std::signbit(static_cast<Float>(diff)); // ������ true, ����� false

	// ���� ���� -> ���� ����
	if (bSign == false)
	{
		Int32 startStep = currentStep - 1;
		for (Uint32 i = 0; i < diffStep; ++i)
		{
			time *= TimeHandler::LOWER_CONVERTION_TIME_TABLE[startStep - i];
		}
	}
	// ���� ���� -> ���� ����
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
		"��", "��", "ȭ", "��", "��", "��", "��"
	};
	
	std::array<std::string, timeUnitCount> strTimeUnits;

	// �� �ð� ���� �ֱ�
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

	// �� �ð� ������ ǥ�� ���� ���ϱ�
	TimeData::TimeOrders& timeOrders = Data()->GetTimeOrders();
	for (Uint32 i = 0; i < timeUnitCount; ++i)
	{
		EnumIdx::TimeUnit::Data orderIdx = timeOrders[i];

		const std::string& strTimeUnit = strTimeUnits[orderIdx];
		if (strTimeUnit.empty() == true) // �ش� �ð� ������ ������� �ʰڴٴ� �ǹ�
		{
			continue;
		}

		strLocalTime += strTimeUnit;
		strLocalTime += delimiter;
	}

	// delimiter ����
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

	// ���� �ð� ������ ���� �ð� ������ ���ٸ� �����ϴ� �ǹ̰� �����ϴ�.
	EnumIdx::TimeUnit::Data prevTimeUnit = timeOrders[orderIdx];
	if (prevTimeUnit == timeUnit)
	{
		return;
	}

	// ���� ���� �ε����� �� ��ü
	timeOrders[orderIdx] = timeUnit;
	timeOrders[prevIdx] = prevTimeUnit;
}