// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 타임 핸들러입니다.
// 시간 변환 등 시간 관련 내용을 다룹니다.
// =====================================================================================
#pragma once

#include "ITimeHandler.h"

class TimeHandler : public ITimeHandler
{
	ONLY_SUBSYSTEM(TimeHandler);

public:
	virtual void SetUp() override;
	virtual void CleanUp() override;

	virtual Uint32 ConvertSecondsToMinutes(Float seconds) const override;
	virtual Uint32 ConvertSecondsToHours(Float seconds) const override;

	virtual void MakeLocalTimeString(OUT std::string& strLocalTime, Char delimiter) override;
};