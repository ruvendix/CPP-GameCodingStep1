// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Ÿ���� �������̽��Դϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonInterface.h"

class ITime : public IService
{
public:
	ITime() = default;
	virtual ~ITime() = default;

	virtual EReturnType SetUp() override { return EReturnType::SUCCESS; }
	virtual EReturnType CleanUp() override { return EReturnType::SUCCESS; }

	virtual void UpdateFrameTime() = 0;

	virtual Float GetDeltaTime() const = 0;
	virtual Float GetTimeScale() const = 0;

	virtual void SetFixedDeltaTime(Int32 FPS) = 0;
	virtual void SetTimeScale(Float timeScale) = 0;
};