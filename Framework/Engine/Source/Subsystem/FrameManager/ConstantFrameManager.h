// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 고정 프레임 타임 관리자입니다.
// =====================================================================================
#pragma once

#include "Base/IFrameManager.h"

// 전방 선언
class ConstantFrameManagerInside;

class ConstantFrameManager final : public IFrameManager
{
	ONLY_SUBSYSTEM_CTOR(ConstantFrameManager);

public:
	virtual void SetUp() override;
	virtual void CleanUp() override;

	virtual void UpdateFrameTime() override;

private:
	std::unique_ptr<ConstantFrameManagerInside> m_spInside = nullptr;
};