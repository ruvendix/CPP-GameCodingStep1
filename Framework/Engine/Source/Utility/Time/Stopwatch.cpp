// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ð� ��ġ�Դϴ�.
// ��� �ð� ��ġ�� ���� �ð��� ���� �־�� �մϴ�.
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
	���� �ð��� �����մϴ�.
*/
void Stopwatch::StartTime()
{
	m_spInside->StartTime();
}

/*
	���� �ð��� �����ϰ� ��� �ð��� ����մϴ�.
*/
Float Stopwatch::EndTime()
{
	return m_spInside->EndTime();
}