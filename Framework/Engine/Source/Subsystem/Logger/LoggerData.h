// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 에러 핸들러에 사용되는 외부 데이터입니다.
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