// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 기능이 없는 경로 관리자입니다.
// 경로 관리자가 초기화되지 않았을 때 사용됩니다.
// FIND_SUBSYSTEM() 매크로를 통해서만 사용됩니다.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "IPathManager.h"

class IPathManagerNull : public IPathManager
{
public:
	virtual void StartUp() OVERRIDE_EMPTY_FUNC;
	virtual void CleanUp() OVERRIDE_EMPTY_FUNC;

	virtual const std::string& FrameworkAbsolutePath() CONST_OVERRIDE_RETURN_FUNC(m_str);
	virtual const std::string& FrameworkRelativePath() CONST_OVERRIDE_RETURN_FUNC(m_str);
	virtual Uint32 FrameworkRelativePathStartPos() CONST_OVERRIDE_RETURN_FUNC(0);

	virtual const std::string& ClientAbsolutePath() CONST_OVERRIDE_RETURN_FUNC(m_str);
	virtual const std::string& ClientRelativePath() CONST_OVERRIDE_RETURN_FUNC(m_str);
	virtual Uint32 ClientRelativePathStartPos() CONST_OVERRIDE_RETURN_FUNC(0);

	virtual const Char* ExtractExtension(const std::string_view& strFilePath) CONST_OVERRIDE_RETURN_FUNC("");

private:
	std::string m_str;
};