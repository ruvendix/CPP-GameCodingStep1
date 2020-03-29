// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 게임과 관계없는 공통적인 설정 내용 모음입니다.
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