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

#include "Common\CommonType.h"
#include "Common\CommonMacro.h"
#include "Element\NameTag.h"

class TriggerTimer final
{
public:
	using TriggerTimerCallback = std::function<void()>;

#pragma region ������ �� �Ҹ���
	TriggerTimer() = default;
	~TriggerTimer() = default;
#pragma endregion

	void AddDeltaTime();

	void Reset()
	{
		m_elapsedTime -= m_triggerTime; // ¥���� �ð����� �����մϴ�.
	}

	void CallTriggerTimerFunc()
	{
		m_triggerTimerCallback();
	}

	bool IsRepeat() const
	{
		return (m_bRepeat == true);
	}

	bool IsTriggerTime() const
	{
		return (m_elapsedTime > m_triggerTime);
	}

	void setTime(Real32 triggerTime)
	{
		m_triggerTime = triggerTime;
	}

	void setFunc(TriggerTimerCallback triggerTimerCallback)
	{
		m_triggerTimerCallback = triggerTimerCallback;
	}

	void setRepeat(bool bRepeat)
	{
		m_bRepeat = bRepeat;
	}

private:
	Real32 m_elapsedTime = 0.0f; // ��� �ð�
	Real32 m_triggerTime = 0.0f; // Ʈ���� �ߵ� �ð�
	bool m_bRepeat = false;
	TriggerTimerCallback m_triggerTimerCallback = nullptr;
};

#endif