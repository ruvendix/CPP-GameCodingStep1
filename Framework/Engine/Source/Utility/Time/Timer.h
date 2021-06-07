// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 타이머입니다.
// 지정 시간에서 0이 되었는지를 정확히 맞춰야 하는데 호출 오버헤드를 줄이기 위해
// 델타타임을 이용했습니다. 델타타임은 FrameManagerData에 있습니다.
// =====================================================================================
#pragma once

#include "Common/CommonType.h"

// 전방 선언
class TimerInside;

class Timer
{
public:
	Timer();
	~Timer();

	Bool UpdateTime();

	void Enable() { m_bEnable = true; }
	void Disable() { m_bEnable = false; }

	void SetTargetTime(Float targetTime) { m_targetTime = targetTime; }
	void SetLoop(Bool bLoop) { m_bLoop = bLoop; }

private:
	Bool m_bEnable = true;
	Bool m_bLoop = false;

	Float m_targetTime = 0.0f;
	std::unique_ptr<TimerInside> m_spInside = nullptr;
};