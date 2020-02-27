#include "PCH.h"
#include "StopwatchTimer.h"

/*
���� �ð��� �����մϴ�.
*/
void StopwatchTimer::StartTime()
{
	m_startTime = ::timeGetTime();
	//m_startTime = std::chrono::steady_clock::now();
}

/*
���� �ð��� �����ϰ� �ð� ������ ����մϴ�.
*/
Real32 StopwatchTimer::EndTime()
{
	m_endTime = ::timeGetTime();
	//m_endTime = std::chrono::steady_clock::now();

	// �и��� �����̹Ƿ� 0.001f�� ������� �ʴ����� ��ȯ�� �� �־��!
	Real32 timeInterval = (m_endTime - m_startTime) * 0.001f;
	//DEBUG_LOG("���� �ð�(%d) ~ ���� �ð�(%d) : (%f)��", m_startTime, m_endTime, timeInterval);

	//std::chrono::duration<Real32> timeInterval = m_endTime - m_startTime; // �⺻ ������ ��!
	//DEBUG_LOG("�ð� ���� : (%f)��", timeInterval.count());

	return timeInterval;
	//return timeInterval.count();
}