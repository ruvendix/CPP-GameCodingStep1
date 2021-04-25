// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 시간 장치입니다.
// 모든 시간 장치는 시작 시간을 갖고 있어야 합니다.
// =====================================================================================
#include "EnginePCH.h"
#include "Stopwatch.h"

/*
	시작 시간과 종료 시간을 초기화합니다.
*/
Stopwatch::Stopwatch()
{
	StartTime();
	m_endTimePoint = m_startTimePoint;
}

/*
	시작 시간을 측정합니다.
*/
void Stopwatch::StartTime()
{
	m_startTimePoint = std::chrono::system_clock::now();
}

/*
	종료 시간을 측정하고 경과 시간을 계산합니다.
*/
void Stopwatch::EndTime()
{
	m_endTimePoint = std::chrono::system_clock::now();
	std::chrono::duration<Float> duration = m_endTimePoint - m_startTimePoint;
	m_elapsedTime = duration.count();
}

/*
	시작 시간에 종료 시간을 대입하고 경과 시간을 초기화합니다.
*/
void Stopwatch::RestartTime()
{
	m_elapsedTime = 0.0f;
	m_startTimePoint = m_endTimePoint;
}