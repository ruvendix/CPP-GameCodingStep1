// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �����Ӱ� ���õ� �ð��� �ٷ�ϴ�.
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