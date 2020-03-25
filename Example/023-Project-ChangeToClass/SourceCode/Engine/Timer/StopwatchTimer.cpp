#include "PCH.h"
#include "StopwatchTimer.h"

/*
시작 시간을 측정합니다.
*/
void StopwatchTimer::StartTime()
{
	m_startTime = std::chrono::steady_clock::now();
}

/*
종료 시간을 측정하고 시간 간격을 계산합니다.
*/
Real32 StopwatchTimer::EndTime()
{
	m_endTime = std::chrono::steady_clock::now();

	std::chrono::duration<Real32> timeIntervalue = m_endTime - m_startTime; // 기본 단위는 초!
	//DEBUG_LOG("시간 간격 : (%f)초", timeInterval.count());

	return timeIntervalue.count();
}