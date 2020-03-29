// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���Ӱ� ������� �������� ���� ���� �����Դϴ�.
// =====================================================================================

#ifndef CONFIG_CONTEXT__H__
#define CONFIG_CONTEXT__H__

#include "Common\CommonNecessary.h"
#include "Common\CommonStruct.h"
#include "Common\CommonMacro.h"

class ConfigCtx final
{
	DECLARE_PHOENIX_SINGLETON(ConfigCtx);

public:
	const SizeInfo& getResoultion() const
	{
		return m_resoultion;
	}

	void setResoultion(const SizeInfo& resolution)
	{
		m_resoultion = resolution;
	}

private:
	SizeInfo m_resoultion;
};

#endif