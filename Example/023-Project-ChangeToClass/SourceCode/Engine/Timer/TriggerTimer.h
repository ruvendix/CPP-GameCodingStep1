// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 설정된 시간마다 이벤트가 발생하는 타이머입니다.
// 반복으로 설정되어있으면 이벤트가 주기적으로 발생합니다.
// 단독으로 사용될 수는 없고 매니저를 이용해야 합니다.
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

#pragma region 생성자 및 소멸자
	TriggerTimer() = default;
	~TriggerTimer() = default;
#pragma endregion

	void AddDeltaTime();

	void Reset()
	{
		m_elapsedTime -= m_triggerTime; // 짜투리 시간까지 생각합니다.
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
	Real32 m_elapsedTime = 0.0f; // 경과 시간
	Real32 m_triggerTime = 0.0f; // 트리거 발동 시간
	bool m_bRepeat = false;
	TriggerTimerCallback m_triggerTimerCallback = nullptr;
};

#endif