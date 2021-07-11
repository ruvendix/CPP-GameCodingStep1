// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 파일 핸들러입니다.
// 외부에서 받은 파일을 열거나 닫는 기능이 있습니다.
// =====================================================================================
#pragma once

#include "Base/IFileHandler.h"

class FileHandler : public IFileHandler
{
	ONLY_SUBSYSTEM(FileHandler);

public:
	virtual void SetUp();
	virtual void CleanUp();

	virtual Bool OpenFileStream(const std::string_view& strFilePath,
		EFileMode fileMode, EAccessMode accessMode, OUT FILE** ppFile) const override;

	virtual void CloseFileStream(FILE* pFile) const override;
};