// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 프레임 타임 관리자입니다.
// FPS, 델타타임 등을 관리합니다.
// =====================================================================================
#pragma once

#include "Subsystem/ISubsytem.h"
#include "FrameTimeManagerData.h"

class IFrameTimeManager : public ISubsystem
{
	GENERATE_SUBSYSTEM_ID(ESubsystemID::FRAME_TIME_MANAGER);
	GENERATE_SUBSYSTEM_DATA(FrameTimeManagerData);

public:
	static Float ConvertFPS_ToFixedDeltaTime(Int32 FPS)
	{
		return (1.0f / static_cast<Float>(FPS));
	}

	IFrameTimeManager() = default;
	virtual ~IFrameTimeManager() = default;

	virtual void SetUp() override EMPTY_FUNC;
	virtual void CleanUp() override EMPTY_FUNC;

	virtual void UpdateFrameTime() PURE_FUNC;
};