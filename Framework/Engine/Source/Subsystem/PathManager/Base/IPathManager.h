// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 경로 관리자의 인터페이스입니다.
// =====================================================================================
#pragma once

#include "Subsystem/ISubsytem.h"

class IPathManager : public ISubsystem
{
	GENERATE_SUBSYSTEM(ESubsystemType::PATH_MANAGER);

public:
	IPathManager() = default;
	virtual ~IPathManager() = default;

	virtual const std::string& FrameworkAbsolutePath() CONST_PURE_FUNC;
	virtual const std::string& FrameworkRelativePath() CONST_PURE_FUNC;
	virtual Uint32 FrameworkRelativePathStartPos() CONST_PURE_FUNC;

	virtual const std::string& ClientAbsolutePath() CONST_PURE_FUNC;
	virtual const std::string& ClientRelativePath() CONST_PURE_FUNC;
	virtual Uint32 ClientRelativePathStartPos() CONST_PURE_FUNC;

	virtual const Char* ExtractExtension(const std::string_view& strFilePath) CONST_PURE_FUNC;
};