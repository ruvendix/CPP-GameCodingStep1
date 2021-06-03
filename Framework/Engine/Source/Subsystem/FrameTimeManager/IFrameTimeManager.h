// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������ Ÿ�� �������Դϴ�.
// FPS, ��ŸŸ�� ���� �����մϴ�.
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