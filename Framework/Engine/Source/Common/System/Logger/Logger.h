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

#include "Common/CommonInterface.h"
#include "LogEnum.h"

#pragma region 전방 선언
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