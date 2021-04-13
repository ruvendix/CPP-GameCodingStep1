// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 로그 카테고리의 기반입니다.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "Common/CommonType.h"

class LogCategoryBase
{
public:
	LogCategoryBase(const std::string_view& strName)
	{
		m_strName = strName;
	}

	virtual ~LogCategoryBase() = default;

	const std::string& getName() const
	{
		return m_strName;
	}

	void Activate()
	{
		m_bActivation = true;
	}

	void Deactivate()
	{
		m_bActivation = false;
	}

private:
	Bool m_bActivation = true;
	std::string m_strName;
};