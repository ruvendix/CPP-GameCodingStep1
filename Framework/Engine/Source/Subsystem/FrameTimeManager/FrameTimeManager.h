// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 프레임과 관련된 시간을 다룹니다.
// =====================================================================================
#pragma once

#include "IFrameTimeManager.h"
#include "Utility/Time/Stopwatch.h"
#include "Utility/Time/Timer.h"

class FrameTimeManager final : public IFrameTimeManager
{
	ONLY_SUBSYSTEM(FrameTimeManager);

public:
	virtual void SetUp() override;
	virtual void CleanUp() override;

	virtual void UpdateFrameTime() override;

	virtual Float ObtainDeltaTime() const override
	{ 
		return m_deltaTime;
	}

	virtual Float ObtainTimeScale() const override
	{ 
		return m_timeScale;
	}

	virtual void ModifyFixedDeltaTime(Int32 FPS) override
	{
		m_fixedDeltaTime = 1.0f / static_cast<Float>(FPS);
	}

	virtual void ModifyTimeScale(Float timeScale) override
	{
		m_timeScale = timeScale;
	}

private:
	Float m_deltaTime = 0.0f;
	Float m_fixedDeltaTime = 0.0f;
	Float m_timeScale = 1.0f;

	Int32 m_frameCount = 0;

	Timer m_FPSTimer;
	Stopwatch m_deltaTimeStopwatch;
};