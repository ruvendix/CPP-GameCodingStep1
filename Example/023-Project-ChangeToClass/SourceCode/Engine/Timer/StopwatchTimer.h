// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ð� ������ ������ Ÿ�̸��Դϴ�. (�����ġ)
// ���� �ð��� ���� �ð� �� �� �����մϴ�.
// =====================================================================================

#ifndef STOPWATCH_TIMER__H__
#define STOPWATCH_TIMER__H__

#include "Common\CommonType.h"
#include "Common\CommonMacro.h"
#include "Common\CommonNecessary.h"

using TimePoint = std::chrono::system_clock::time_point;

class StopwatchTimer
{
	DECLARE_ROOT_RTTI(StopwatchTimer);

public:
#pragma region ������ �� �Ҹ���
	StopwatchTimer() = default;
	~StopwatchTimer() = default;
#pragma endregion

	void StartTime();
	void EndTime();

	void SwapTime()
	{
		m_startTime = m_endTime;
	}

	TimePoint getStartTime() const
	{
		return m_startTime;
	}

	TimePoint getEndTime() const
	{
		return m_endTime;
	}

	Real32 getElaspedTime() const
	{
		return m_elaspedTime;
	}

private:
	TimePoint m_startTime;
	TimePoint m_endTime;
	Real32 m_elaspedTime = 0.0f;
};

#endif