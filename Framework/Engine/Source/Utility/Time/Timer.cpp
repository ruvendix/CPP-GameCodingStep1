// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Ÿ�̸��Դϴ�.
// ��ǥ �ð������� ��� �ð��� ��Ȯ�� ����� �ϹǷ� ��ŸŸ���� �̿��մϴ�.
// ��ŸŸ���� Time Ŭ������ �ֽ��ϴ�. (�̸��� ����ϴϱ� ����!)
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
	��ŸŸ���� �����ϸ鼭 ��ǥ �ð����� �޼��ߴ��� Ȯ���մϴ�.
	��ǥ �ð����� �޼������� true��, �ƴ϶�� false�� ��ȯ�մϴ�.
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