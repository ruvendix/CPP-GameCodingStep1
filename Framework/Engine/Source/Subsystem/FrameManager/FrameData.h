// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 프레임 매니저에 사용되는 외부 데이터입니다.
// =====================================================================================
#pragma once

#include "Common/CommonType.h"
#include "Subsystem/SubsystemData.h"

class FrameData final : public SubsystemData
{
public:
	FrameData() = default;
	~FrameData() = default;

	Int32 GetFrameRate() const { return m_frameRate; }
	void SetFrameRate(Int32 frameCount) { m_frameRate = frameCount; }

	Float GetDeltaTime() const { return m_deltaTime; }
	void SetDeltaTime(Float deltaTime) { m_deltaTime = deltaTime; }

	// 아직 사용하는 곳이 없습니다.
	DECLSPEC_DEPRECATED Float GetTimeScale() const { return m_timeScale; }
	DECLSPEC_DEPRECATED void SetTimeScale(Float timeScale) { m_timeScale = timeScale; }

private:
	Int32 m_frameRate = 0; // Frame Count와 같습니다.
	Float m_deltaTime = 0.0f;
	Float m_timeScale = 1.0f;
};