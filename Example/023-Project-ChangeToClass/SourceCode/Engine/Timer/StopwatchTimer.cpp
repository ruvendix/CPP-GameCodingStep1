// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 시간 측정이 가능한 타이머입니다. (스톱워치)
// 시작 시간과 종료 시간 둘 다 저장합니다.
// =====================================================================================

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