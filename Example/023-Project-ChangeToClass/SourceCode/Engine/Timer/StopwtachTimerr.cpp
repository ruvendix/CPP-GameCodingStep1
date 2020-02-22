#include "PCH.h"
#include "StopwtachTimerr.h"

/*
���� �ð��� �����մϴ�.
*/
void StopwatchTimer::StartTime()
{
	m_startTime = ::timeGetTime();
}

/*
���� �ð��� �����մϴ�.
*/
void StopwatchTimer::EndTime()
{
	m_endTime = ::timeGetTime();
}

/*
������ ������ �̿��ؼ� ����� ����ϰ� �����ݴϴ�.
*/
void StopwatchTimer::ShowResult()
{
	if (m_endTime == 0)
	{
		return;
	}

	// �и��� �����̹Ƿ� 0.001f�� ������� �ʴ����� ��ȯ�� �� �־��!
	Real32 startSeconds = m_startTime * 0.001f;
	Real32 endSeconds = m_endTime * 0.001f;
	Real32 timeInterval = (endSeconds - startSeconds) * 0.001f;
	DEBUG_LOG("���� �ð�(%d��) ~ ���� �ð�(%d��) : %f\n", startSeconds, endSeconds, timeInterval);
}