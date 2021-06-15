// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ΰ��� �������̽��Դϴ�.
// =====================================================================================
#pragma once

#include "Subsystem/ISubsytem.h"

// ���� ����
class LogCategoryBase;

class ILogger : public ISubsystem
{
	GENERATE_SUBSYSTEM_TYPE(ESubsystemType::LOGGER);

public:
	ILogger() = default;
	virtual ~ILogger() = default;

	virtual void Trace(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szFilePath, Int32 line) const PURE_FUNC;

	virtual void Assert(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szFilePath, Int32 line) const PURE_FUNC;

	virtual void Info(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szFilePath, Int32 line) const PURE_FUNC;

	virtual void Warning(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szFilePath, Int32 line) const PURE_FUNC;

	virtual void Error(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szFilePath, Int32 line) const PURE_FUNC;

	virtual void Fatal(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szFilePath, Int32 line) const PURE_FUNC;
};