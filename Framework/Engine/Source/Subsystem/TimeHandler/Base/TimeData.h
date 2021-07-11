// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 타임 핸들러에 사용되는 외부 데이터입니다.
// =====================================================================================
#pragma once

#include "TimeEnum.h"
#include "Subsystem/SubsystemData.h"

class TimeData final : public SubsystemData
{
public:
	using TimeUnits = std::bitset<EnumIdx::TimeUnit::COUNT>;
	using TimeOrders = std::array<EnumIdx::TimeUnit::Data, EnumIdx::TimeUnit::COUNT>;

	TimeData();
	~TimeData() = default;

	Float GetTimeScale() const { return m_timeScale; }
	void SetTimeScale(Float timeScale) { m_timeScale = timeScale; }

	TimeUnits& GetTimeUnits() { return m_timeUnits; }
	TimeOrders& GetTimeOrders() { return m_timeOrders; }

private:
	Float m_timeScale = 1.0f;
	TimeUnits m_timeUnits;
	TimeOrders m_timeOrders;
};