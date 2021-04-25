// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 타임의 인터페이스입니다.
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