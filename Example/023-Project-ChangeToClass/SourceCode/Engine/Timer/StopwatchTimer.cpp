#include "PCH.h"
#include "StopwatchTimer.h"

/*
시작 시간을 측정합니다.
*/
void StopwatchTimer::StartTime()
{
	m_startTime = ::timeGetTime();
}

/*
종료 시간을 측정하고 시간 간격을 계산합니다.
*/
Real32 StopwatchTimer::EndTime()
{
	m_endTime = ::timeGetTime();

	// 밀리초 단위이므로 0.001f를 곱해줘야 초단위로 변환할 수 있어요!
	Real32 timeInterval = (m_endTime - m_startTime) * 0.001f;
	//DEBUG_LOG("시작 시간(%d) ~ 종료 시간(%d) : (%f)\n", m_startTime, m_endTime, timeInterval);

	return timeInterval;
}