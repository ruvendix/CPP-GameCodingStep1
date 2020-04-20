// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������ �ð����� �̺�Ʈ�� �߻��ϴ� Ÿ�̸��Դϴ�.
// �ݺ����� �����Ǿ������� �̺�Ʈ�� �ֱ������� �߻��մϴ�.
// �ܵ����� ���� ���� ���� �Ŵ����� �̿��ؾ� �մϴ�.
// =====================================================================================

#ifndef TRIGGER_TIMER__H__
#define TRIGGER_TIMER__H__

#include "Element\NameTag.h"
#include "StopwatchTimer.h"

using TriggerTimerCallback = std::function<void()>;

class TriggerTimer final : public StopwatchTimer
{
	DECLARE_RTTI(TriggerTimer, StopwatchTimer);

public:
#pragma region ������ �� �Ҹ���
	TriggerTimer() = default;
	~TriggerTimer() = default;
#pragma endregion

	void AddElapsedTime();
	void UpdateKeepTime();

	void Reset()
	{
		m_elapsedTime -= m_triggerTime; // ¥���� �ð����� �����մϴ�.
	}

	void CallTriggerTimerFunc()
	{
		m_callback();
	}

	bool IsRepeat() const
	{
		return (m_bRepeat == true);
	}

	bool IsTriggerTime() const
	{
		return (m_elapsedTime > m_triggerTime);
	}

	bool IsExistKeepTime() const
	{
		return (m_keepTime > 0.0f);
	}

	bool IsRender() const
	{
		return (m_bRender == true);
	}

	bool HasKeepTime() const
	{
		return (IsTriggerTime() && IsExistKeepTime());
	}

	void setTime(Real32 triggerTime)
	{
		m_triggerTime = triggerTime;
	}

	void setKeepTime(Real32 keepTime)
	{
		m_keepTime = keepTime;
	}

	void setCallback(TriggerTimerCallback callback)
	{
		m_callback = callback;
	}

	void setRepeat(bool bRepeat)
	{
		m_bRepeat = bRepeat;
	}

	void setRender(bool bRender)
	{
		m_bRender = bRender;
	}

private:
	Real32 m_elapsedTime = 0.0f; // ��� �ð�
	Real32 m_triggerTime = 0.0f; // Ʈ���� �ߵ� �ð�
	Real32 m_keepTime = 0.0f; // ���� �ð�

	bool m_bRepeat = false;
	bool m_bRender = false; // ������ ����

	TriggerTimerCallback m_callback = nullptr;
};

#endif