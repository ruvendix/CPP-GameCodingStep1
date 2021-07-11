// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 타이머입니다.
// 목표 시간까지의 경과 시간을 정확히 맞춰야 하므로 델타타임을 이용합니다.
// 델타타임은 Time 클래스에 있습니다. (이름이 비슷하니까 주의!)
// =====================================================================================
#include "EnginePCH.h"
#include "Timer.h"

class TimerInside final
{
public:
	TimerInside() = default;
	~TimerInside() = default;
	
	Float UpdateTime();
	void ResetTime(Float targetTime);

private:
	Float m_localTime = 0.0f;
};

Float TimerInside::UpdateTime()
{
	m_localTime += DELTA_TIME;
	return m_localTime;
}

void TimerInside::ResetTime(Float targetTime)
{
	RX_ASSERT(m_localTime >= targetTime);
	m_localTime -= targetTime;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
Timer::Timer()
{
	m_spInside = std::make_unique<TimerInside>();
}

Timer::~Timer()
{

}

/*
	델타타임을 누적하면서 목표 시간까지 달성했는지 확인합니다.
	목표 시간까지 달성했으면 true를, 아니라면 false를 반환합니다.
*/
Bool Timer::UpdateTime()
{
	if (m_bEnable == false)
	{
		return false;
	}

	Float remainTime = m_targetTime - m_spInside->UpdateTime();
	if (remainTime > 0.0f)
	{
		RX_TRACE("remainTime: %f", remainTime);
		return false;
	}

	m_spInside->ResetTime(m_targetTime);

	if (m_bLoop == false)
	{
		m_bEnable = false;
	}

	return true;
}