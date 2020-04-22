// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 시간 측정이 가능한 타이머입니다. (스톱워치)
// 시작 시간과 종료 시간 둘 다 저장합니다.
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
#pragma region 생성자 및 소멸자
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