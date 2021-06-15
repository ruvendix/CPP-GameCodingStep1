// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 경로 매니저의 인터페이스입니다.
// =====================================================================================
#pragma once

#include "Subsystem/ISubsytem.h"

class IPathManager : public ISubsystem
{
	GENERATE_SUBSYSTEM_TYPE(ESubsystemType::PATH_MANAGER);

public:
	IPathManager() = default;
	virtual ~IPathManager() = default;

	virtual const std::string& FrameworkAbsolutePath() const PURE_FUNC;
	virtual const Uint32 FrameworkRelativePathStartPos() const PURE_FUNC;

	virtual const std::string& ClientAbsolutePath() const PURE_FUNC;

	virtual const Char* ExtractExtension(const std::string_view& strFilePath) const PURE_FUNC;
};