// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 프레임 타임 관리자의 인터페이스입니다.
// 외부 데이터와 함수를 갖고 있으니 추상 클래스이기도 합니다.
// =====================================================================================
#pragma once

#include "Subsystem/ISubsytem.h"
#include "FrameData.h"

class IFrameManager : public ISubsystem
{
	GENERATE_SUBSYSTEM(ESubsystemType::FRAME_MANAGER);
	GENERATE_SUBSYSTEM_DATA(FrameData);

public:
	static Float ConvertFPS_ToFixedDeltaTime(Int32 FPS)
	{
		return (1.0f / static_cast<Float>(FPS));
	}

	IFrameManager() = default;
	virtual ~IFrameManager() = default;

	virtual void UpdateFrameTime() PURE_FUNC;
};