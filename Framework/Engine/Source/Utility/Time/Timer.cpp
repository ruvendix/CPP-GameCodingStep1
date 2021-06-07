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

#include "Subsystem/FrameManager/IFrameManager.h"

class TimerInside final
{
public:
	TimerInside() = default;
	~TimerInside() = default;
	
	Float UpdateTime();
	void ResetTime();

private:
	Float m_localTime = 0.0f;
};

Float TimerInside::UpdateTime()
{
	m_localTime += DELTA_TIME;
	return m_localTime;
}

void TimerInside::ResetTime()
{
	m_localTime = 0.0f;
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
		RX_SIMPLE_TRACE("remainTime: %f", remainTime);
		return false;
	}

	m_spInside->ResetTime();

	if (m_bLoop == false)
	{
		m_bEnable = false;
	}

	return true;
}