// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 기능이 없는 타임 핸들러입니다.
// 타임 핸들러가 초기화되지 않았을 때 사용됩니다.
// FIND_SUBSYSTEM() 매크로를 통해서만 사용됩니다.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "ITimeHandler.h"

class ITimeHandlerNull : public ITimeHandler
{
public:
	virtual void StartUp() OVERRIDE_EMPTY_FUNC;
	virtual void CleanUp() OVERRIDE_EMPTY_FUNC;

	virtual Float ConvertTime(Float time, EConvertionTimeUnit src, EConvertionTimeUnit dest) CONST_OVERRIDE_RETURN_FUNC(0.0f);
	virtual void MakeLocalTimeString(std::string& strLocalTime, Char delimiter) OVERRIDE_EMPTY_FUNC;

	virtual void ActivateTimeUnit(EnumIdx::TimeUnit::Data timeUnit) OVERRIDE_EMPTY_FUNC;
	virtual void DeactivateTimeUnit(EnumIdx::TimeUnit::Data timeUnit) OVERRIDE_EMPTY_FUNC;
	virtual bool CheckTimeUnit(EnumIdx::TimeUnit::Data timeUnit) CONST_OVERRIDE_RETURN_FUNC(true);

	virtual void ChangeTimeOrder(EnumIdx::TimeUnit::Data timeUnit, Uint32 orderIdx) OVERRIDE_EMPTY_FUNC;
};