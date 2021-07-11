// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 타임 핸들러에 사용되는 외부 데이터입니다.
// =====================================================================================
#pragma once

#include "EnginePCH.h"
#include "TimeData.h"

TimeData::TimeData()
{
	for (Int32 i = 0; i < EnumIdx::TimeUnit::COUNT; ++i)
	{
		m_timeUnits.set(false);
		m_timeOrders[i] = EnumIdx::TimeUnit::UNKNOWN;
	}
}