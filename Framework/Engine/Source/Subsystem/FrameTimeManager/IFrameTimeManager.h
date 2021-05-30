// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Ÿ���� �������̽��Դϴ�.
// =====================================================================================
#pragma once

#include "Subsystem/ISubsytem.h"

class IFrameTimeManager : public ISubsystem
{
	GENERATE_MATCH_TYPE(ESubsystemType::FRAME_TIME_MANAGER)

public:
	IFrameTimeManager() = default;
	virtual ~IFrameTimeManager() = default;

	virtual void SetUp() override { }
	virtual void CleanUp() override { }

	virtual void UpdateFrameTime() = 0;

	virtual Float GetDeltaTime() const = 0;
	virtual Float GetTimeScale() const = 0;

	virtual void SetFixedDeltaTime(Int32 FPS) = 0;
	virtual void SetTimeScale(Float timeScale) = 0;
};