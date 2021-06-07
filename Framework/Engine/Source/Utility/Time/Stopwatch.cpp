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

class StopwatchInside final
{
public:
	StopwatchInside() = default;
	~StopwatchInside() = default;

	void StartTime();
	Float EndTime();

private:
	std::chrono::system_clock::time_point m_startTimePoint;
};

void StopwatchInside::StartTime()
{
	m_startTimePoint = std::chrono::system_clock::now();
}

Float StopwatchInside::EndTime()
{
	std::chrono::system_clock::time_point endTimePoint = std::chrono::system_clock::now();
	std::chrono::duration<Float> duration = endTimePoint - m_startTimePoint;
	m_startTimePoint = endTimePoint;
	return duration.count();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
Stopwatch::Stopwatch()
{
	m_spInside = std::make_unique<StopwatchInside>();
}

Stopwatch::~Stopwatch()
{

}

/*
	시작 시간을 측정합니다.
*/
void Stopwatch::StartTime()
{
	m_spInside->StartTime();
}

/*
	종료 시간을 측정하고 경과 시간을 계산합니다.
*/
Float Stopwatch::EndTime()
{
	return m_spInside->EndTime();
}