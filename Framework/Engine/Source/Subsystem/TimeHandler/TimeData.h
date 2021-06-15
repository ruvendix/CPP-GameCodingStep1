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
	using TimeOption = std::bitset<EnumIdx::TimeOption::COUNT>;
	using TimeOrders = std::array<EnumIdx::TimeOption::Data, EnumIdx::TimeOption::COUNT>;

	TimeData() = default;
	~TimeData() = default;

	Float GetTimeScale() const { return m_timeScale; }
	void SetTimeScale(Float timeScale) { m_timeScale = timeScale; }

	TimeOption& GetTimeOption() { return m_timeOption; }
	TimeOrders& GetTimeOrders() { return m_timeOrders; }

private:
	Float m_timeScale = 1.0f;
	TimeOption m_timeOption;
	TimeOrders m_timeOrders;
};