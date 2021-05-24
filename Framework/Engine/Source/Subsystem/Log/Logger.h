// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������̳� ������ ã�Ƴ� �� ����Ǵ� ���ڿ��� ����� �� ����մϴ�.
// �ܼ�â�Ӹ� �ƴ϶� ���α׷� ȭ�鿡�� �α׸� ����մϴ�. 
// =====================================================================================
#pragma once

#include "ILogger.h"

class Logger final : public ILogger
{
public:
	Logger();
	virtual ~Logger();

	virtual void SetUp() override;
	virtual void CleanUp() override;

	virtual void Trace(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) const override;

	virtual void Assert(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) const override;

	virtual void Info(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) const override;

	virtual void Warning(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) const override;

	virtual void Error(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) const override;

	virtual void Fatal(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line) const override;

private:
	class LoggerInternal* m_pInternal = nullptr;
};