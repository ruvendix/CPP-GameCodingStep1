// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �ڵ鷯�� ���Ǵ� �ܺ� �������Դϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonType.h"
#include "Subsystem/SubsystemData.h"
#include "LogEnum.h"

class LoggerData final : public SubsystemData
{
public:
	LoggerData() = default;
	~LoggerData() = default;

	bool IsActivateOption(EnumIdx::LogOption::Data value) const
	{ 
		return m_logOption.test(value);
	}

	void ActivateOption(EnumIdx::LogOption::Data value)
	{ 
		m_logOption.set(value, true);
	}

	void DeactivateOption(EnumIdx::LogOption::Data value)
	{ 
		m_logOption.set(value, false);
	}

private:
	std::bitset<EnumIdx::LogOption::COUNT> m_logOption;
};