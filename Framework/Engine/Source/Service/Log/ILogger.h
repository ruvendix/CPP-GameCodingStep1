// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ΰ��� �������̽��Դϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonInterface.h"
#include "LogCategoryBase.h"

class ILogger : public IDefault
{
public:
	ILogger() = default;
	virtual ~ILogger() = default;

	virtual EReturnType SetUp() DEFAULT_FUNC
	virtual EReturnType CleanUp() DEFAULT_FUNC

	virtual void ActivateCategory(LogCategoryBase* pCategory) PURE_FUNC
	virtual void DeactivateCategory(LogCategoryBase* pCategory) PURE_FUNC

	virtual void Trace(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) PURE_FUNC

	virtual void Assert(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) PURE_FUNC

	virtual void Info(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) PURE_FUNC

	virtual void Warning(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) PURE_FUNC

	virtual void Error(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) PURE_FUNC

	virtual void Fatal(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) PURE_FUNC
};