// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �α� ī�װ��� ����Դϴ�.
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

	Bool CheckActivate() const;

	void Activate() { m_bActivation = true; }
	void Deactivate() { m_bActivation = false; }

	const std::string& GetName() const { return m_strName; }

private:
	Bool m_bActivation = true;
	std::string m_strName;
};