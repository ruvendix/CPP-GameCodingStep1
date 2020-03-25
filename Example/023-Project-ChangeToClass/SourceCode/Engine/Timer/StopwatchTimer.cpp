#include "PCH.h"
#include "StopwatchTimer.h"

/*
���� �ð��� �����մϴ�.
*/
void StopwatchTimer::StartTime()
{
	m_startTime = std::chrono::steady_clock::now();
}

/*
���� �ð��� �����ϰ� �ð� ������ ����մϴ�.
*/
Real32 StopwatchTimer::EndTime()
{
	m_endTime = std::chrono::steady_clock::now();

	std::chrono::duration<Real32> timeIntervalue = m_endTime - m_startTime; // �⺻ ������ ��!
	//DEBUG_LOG("�ð� ���� : (%f)��", timeInterval.count());

	return timeIntervalue.count();
}