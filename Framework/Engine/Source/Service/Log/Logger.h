// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 디버깅이나 에러를 찾아낼 때 도움되는 문자열을 출력할 때 사용합니다.
// 콘솔창뿐만 아니라 프로그램 화면에도 로그를 출력합니다. 
// =====================================================================================
#pragma once

#include "ILogger.h"

class Logger : public ILogger
{
public:
	Logger() = default;
	virtual ~Logger() = default;

	virtual EReturnType SetUp() override;
	virtual EReturnType CleanUp() override;

	virtual void Trace(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) override;

	virtual void Assert(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) override;

	virtual void Info(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) override;

	virtual void Warning(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) override;

	virtual void Error(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) override;

	virtual void Fatal(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) override;
};