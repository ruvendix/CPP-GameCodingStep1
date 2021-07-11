// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������ Ÿ�� �������� �������̽��Դϴ�.
// �ܺ� �����Ϳ� �Լ��� ���� ������ �߻� Ŭ�����̱⵵ �մϴ�.
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