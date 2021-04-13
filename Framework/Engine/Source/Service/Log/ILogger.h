// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 로거의 인터페이스입니다.
// =====================================================================================
#pragma once

#include "common/CommonMacro.h"
#include "Common/CommonEnum.h"
#include "Common/CommonInterface.h"

#include "LogCategoryBase.h"

class ILogger : public IDefault
{
public:
	ILogger() = default;
	virtual ~ILogger() = default;

	virtual EReturnType SetUp() DEFAULT_FUNC
	virtual EReturnType CleanUp() DEFAULT_FUNC

	virtual void Trace(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) = 0;

	virtual void Assert(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) = 0;

	virtual void Info(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) = 0;

	virtual void Warning(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) = 0;

	virtual void Error(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) = 0;

	virtual void Fatal(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) = 0;
};