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
	GENERATE_SUBSYSTEM_ID(ESubsystemID::FRAME_TIME_MANAGER);

public:
	IFrameTimeManager() = default;
	virtual ~IFrameTimeManager() = default;

	virtual void SetUp() override { }
	virtual void CleanUp() override { }

	virtual void UpdateFrameTime() = 0;

	virtual Float ObtainDeltaTime() const = 0;
	virtual void ModifyFixedDeltaTime(Int32 FPS) = 0;

	virtual Float ObtainTimeScale() const = 0;
	virtual void ModifyTimeScale(Float timeScale) = 0;
};