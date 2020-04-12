// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// dynamic_cast�� �����ϱ� ���� ���Ǵ� RTTI�Դϴ�.
// ����� ��忡���� dynamic_cast���� ��������, ������ ��忡���� �����ϴ�.
// =====================================================================================

#ifndef FAST_RTTI__H__
#define FAST_RTTI__H__

#include "Common\CommonType.h"
#include "Common\CommonNecessary.h"

class FastRTTI
{
public:
	FastRTTI(const char* szClassName, const FastRTTI* pParent) :
		m_szClassName(szClassName),
		m_pParent(pParent)
	{

	}

	const char* getClassName() const
	{
		return m_szClassName;
	}

	const FastRTTI* getParent() const
	{
		return m_pParent;
	}

private:
	const char* m_szClassName = "Unknown";
	const FastRTTI* m_pParent = nullptr;
};

#endif