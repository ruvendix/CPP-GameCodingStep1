#include "PCH.h"
#include "StopwtachTimerr.h"

/*
시작 시간을 측정합니다.
*/
void StopwatchTimer::StartTime()
{
	m_startTime = ::timeGetTime();
}

/*
종료 시간을 측정합니다.
*/
void StopwatchTimer::EndTime()
{
	m_endTime = ::timeGetTime();
}

/*
측정된 정보를 이용해서 결과를 계산하고 보여줍니다.
*/
void StopwatchTimer::ShowResult()
{
	if (m_endTime == 0)
	{
		return;
	}

	// 밀리초 단위이므로 0.001f를 곱해줘야 초단위로 변환할 수 있어요!
	Real32 startSeconds = m_startTime * 0.001f;
	Real32 endSeconds = m_endTime * 0.001f;
	Real32 timeInterval = (endSeconds - startSeconds) * 0.001f;
	DEBUG_LOG("시작 시간(%d초) ~ 종료 시간(%d초) : %f\n", startSeconds, endSeconds, timeInterval);
}