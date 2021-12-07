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

#include "Common/CommonInterface.h"
#include "LogEnum.h"

#pragma region ���� ����
class LoggerInside;
class BaseLogCategory;

class ITimeHandler;
class IConsoleHandler;
class IFileHandler;
class IPathManager;
#pragma endregion

class Logger final : public ICommon
{
	GENERATE_LOCAL_SINGLETON(Logger);
	FRIEND_CLASS(LoggerInside);

public:
	virtual void StartUp() override;
	virtual void CleanUp() override;

	virtual void Trace(const BaseLogCategory* pCategory, const std::string_view& strContent,
		const Char* szFilePath, Int32 line) const;

	virtual void Assert(const BaseLogCategory* pCategory, const std::string_view& strContent,
		const Char* szFilePath, Int32 line) const;

	virtual void Info(const BaseLogCategory* pCategory, const std::string_view& strContent,
		const Char* szFilePath, Int32 line) const;

	virtual void Warning(const BaseLogCategory* pCategory, const std::string_view& strContent,
		const Char* szFilePath, Int32 line) const;

	virtual void Error(const BaseLogCategory* pCategory, const std::string_view& strContent,
		const Char* szFilePath, Int32 line) const;

	virtual void Fatal(const BaseLogCategory* pCategory, const std::string_view& strContent,
		const Char* szFilePath, Int32 line) const;

	bool IsActivateOption(EnumIdx::LogOption::Data value) const
	{
		return m_logOption.test(value);
	}
	
	void ActivateOption(EnumIdx::LogOption::Data value)
	{
		m_logOption.set(value, true);
	}

	void DeactivateOption(EnumIdx::LogOption::Data value)
	{
		m_logOption.set(value, false);
	}

	void SetTimeHandler(ITimeHandler* pTimeHandler) { m_pTimeHandler = pTimeHandler; }
	void SetConsoleHandler(IConsoleHandler* pConsoleHandler) { m_pConsoleHandler = pConsoleHandler; }
	void SetFileHandler(IFileHandler* pFileHandler) { m_pFileHandler = pFileHandler; }
	void SetPathManager(IPathManager* pPathManager) { m_pPathManager = pPathManager; }

private:
	LoggerInside* m_pInside = nullptr;
	std::bitset<EnumIdx::LogOption::COUNT> m_logOption;

	ITimeHandler* m_pTimeHandler = nullptr;
	IConsoleHandler* m_pConsoleHandler = nullptr;
	IFileHandler* m_pFileHandler = nullptr;
	IPathManager* m_pPathManager = nullptr;
};