// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 파일 핸들러의 인터페이스입니다.
// =====================================================================================
#pragma once

#include "Subsystem/ISubsytem.h"
#include "FileEnum.h"

class IFileHandler : public ISubsystem
{
	GENERATE_SUBSYSTEM(ESubsystemType::FILE_HANDLER);

public:
	IFileHandler() = default;
	virtual ~IFileHandler() = default;

	virtual Bool OpenFileStream(const std::string_view& strFilePath,
		EFileMode fileMode, EAccessMode accessMode, OUT FILE** ppFile) CONST_PURE_FUNC;

	virtual void CloseFileStream(FILE* pFile) CONST_PURE_FUNC;
};