// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// dynamic_cast를 개선하기 위해 사용되는 RTTI입니다.
// 디버그 모드에서는 dynamic_cast보다 느리지만, 릴리즈 모드에서는 빠릅니다.
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