// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 타임 핸들러의 인터페이스입니다.
// 외부 데이터와 함수를 갖고 있으니 추상 클래스이기도 합니다.
// =====================================================================================
#pragma once

#include "Subsystem/ISubsytem.h"
#include "TimeData.h"

class ITimeHandler : public ISubsystem
{
	GENERATE_SUBSYSTEM_TYPE(ESubsystemType::TIME_HANDLER);
	GENERATE_SUBSYSTEM_DATA(TimeData);

public:
	static Uint32 ConvertSecondsToMinutes(Float seconds)
	{
		return static_cast<Uint32>(seconds / 60.0f);
	}

	static Uint32 ConvertSecondsToHours(Float seconds)
	{
		return static_cast<Uint32>(seconds / 3600.0f);
	}

	ITimeHandler() = default;
	virtual ~ITimeHandler() = default;
};