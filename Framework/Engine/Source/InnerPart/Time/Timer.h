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
#pragma once

#include "Common/CommonType.h"

class Timer
{
public:
	Timer() = default;
	virtual ~Timer() = default;

	Bool UpdateTime();

	void Enable()
	{
		m_bEnable = true;
	}

	void Disable()
	{
		m_bEnable = false;
	}

	void setTargetTime(Float targetTime)
	{
		m_targetTime = targetTime;
	}

	void setLoop(Bool bLoop)
	{
		m_bLoop = bLoop;
	}

private:
	Bool m_bEnable = true;
	Bool m_bLoop = false;

	Float m_localTime = 0.0f;
	Float m_targetTime = 0.0f;
};