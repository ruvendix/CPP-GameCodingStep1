// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ð� ���� �Լ� �����Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "TimeUtil.h"

/*
Ÿ�� ����Ʈ�� �ѱ� �ð� ǥ�������� ���ڿ��� ����ϴ�.
*/
std::string rx_time::MakeTimeString_HHMMSS(const TimePoint& timePoint)
{
	time_t time = std::chrono::system_clock::to_time_t(timePoint);

	tm timeData;
	::ZeroMemory(&timeData, sizeof(timeData));
	localtime_s(&timeData, &time);

	//DEBUG_LOG("%d��, %d��, %d��, %d��, %d��, %d��",
	//	timeData.tm_year, timeData.tm_mon, timeData.tm_mday, timeData.tm_hour, timeData.tm_min, timeData.tm_sec);

	return common_func::MakeFormatString("%02d�� %02d�� %02d��", timeData.tm_hour, timeData.tm_min, timeData.tm_sec);
}

/*
��� �ð��� �ú��ʷ� ��ȯ�մϴ�.
����Ʈ ���ڸ� �̿��ص� ������ �ǹ̻� �ú��� ������ �Ǿ�� �ϹǷ� �����͸� �̿��մϴ�.
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
