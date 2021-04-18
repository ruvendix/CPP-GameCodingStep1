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

	virtual EReturnType SetUp() { return EReturnType::SUCCESS; }
	virtual EReturnType CleanUp() { return EReturnType::SUCCESS; }

	virtual void ActivateCategory(LogCategoryBase* pCategory) = 0;
	virtual void DeactivateCategory(LogCategoryBase* pCategory) = 0;

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