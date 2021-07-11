// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Ÿ�� �ڵ鷯�� ���Ǵ� �ܺ� �������Դϴ�.
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