// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 기능이 없는 파일 핸들러입니다.
// 파일 핸들러가 초기화되지 않았을 때 사용됩니다.
// FIND_SUBSYSTEM() 매크로를 통해서만 사용됩니다.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "IFileHandler.h"

class IFileHandlerNull : public IFileHandler
{
public:
	virtual void SetUp() OVERRIDE_EMPTY_FUNC;
	virtual void CleanUp() OVERRIDE_EMPTY_FUNC;

	virtual Bool OpenFileStream(const std::string_view& strFilePath, EFileMode fileMode, EAccessMode accessMode, FILE** ppFile) CONST_RETURN_FUNC(true);
	virtual void CloseFileStream(FILE* pFile) CONST_OVERRIDE_EMPTY_FUNC;
};