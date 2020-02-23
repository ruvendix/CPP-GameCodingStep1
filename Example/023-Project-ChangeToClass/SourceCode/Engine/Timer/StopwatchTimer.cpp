#include "PCH.h"
#include "StopwatchTimer.h"

/*
���� �ð��� �����մϴ�.
*/
void StopwatchTimer::StartTime()
{
	m_startTime = ::timeGetTime();
}

/*
���� �ð��� �����ϰ� �ð� ������ ����մϴ�.
*/
Real32 StopwatchTimer::EndTime()
{
	m_endTime = ::timeGetTime();

	// �и��� �����̹Ƿ� 0.001f�� ������� �ʴ����� ��ȯ�� �� �־��!
	Real32 timeInterval = (m_endTime - m_startTime) * 0.001f;
	//DEBUG_LOG("���� �ð�(%d) ~ ���� �ð�(%d) : (%f)\n", m_startTime, m_endTime, timeInterval);

	return timeInterval;
}