// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 디버깅이나 에러를 찾아낼 때 도움되는 문자열을 출력할 때 사용합니다.
// 콘솔창뿐만 아니라 프로그램 화면에도 로그를 출력합니다. 
// =====================================================================================
#include "EnginePCH.h"
#include "Logger.h"

#include "LogEnum.h"

class LoggerInternal
{
public:
	LoggerInternal(Logger* pThis);
	~LoggerInternal() = default;

	void BeginLog(EConsoleRenderingColor renderingColor) const;
	void EndLog() const;
	void PrintDebugOutputLog(OUT std::string& strLog) const;

	Bool MakeLog(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line, OUT std::string& strLog) const;

	void ActivateOption(EnumIdx::LogOption::Data value)
	{
		m_bitsetDetail.set(value, true);
	}

	void DeactivateOption(EnumIdx::LogOption::Data value)
	{
		m_bitsetDetail.set(value, false);
	}

	bool IsActivateOption(EnumIdx::LogOption::Data value) const
	{
		return m_bitsetDetail.test(value);
	}

private:
	Logger* m_pLogger = nullptr;
	std::bitset<EnumIdx::LogOption::END> m_bitsetDetail;
};

/*
	필요한 정보를 설정합니다.
*/
LoggerInternal::LoggerInternal(Logger* pThis)
{
	m_pLogger = pThis;
}

/*
	로그를 출력하기 전에 호출됩니다.
*/
void LoggerInternal::BeginLog(EConsoleRenderingColor renderingColor) const
{
	FIND_SUBSYSTEM(IConsoleHandler)->ChangeRenderingColor(renderingColor, EConsoleRenderingType::TEXT);
}

/*
	로그를 출력한 후에 호출됩니다.
*/
void LoggerInternal::EndLog() const
{
	FIND_SUBSYSTEM(IConsoleHandler)->ResetRenderingColor();
}

/*
	전달받은 인자들을 이용해서 로그 문자열을 만듭니다.
*/
Bool LoggerInternal::MakeLog(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line, OUT std::string& strLog) const
{
	std::string strCategory;
	if (pCategory != nullptr)
	{
		if (pCategory->CheckActivate() == false)
		{
			return false;
		}

		strCategory = pCategory->getName() + ": ";
	}

	if ((IsActivateOption(EnumIdx::LogOption::TIME)) &&
		(szTime != nullptr))
	{
		strLog += " [";
		strLog += szTime;
		strLog += "]";
	}

	if ((IsActivateOption(EnumIdx::LogOption::FILEPATH_AND_LINE)) &&
		(szFilePath != nullptr))
	{
		strLog += " [";
		strLog += szFilePath;
		strLog += "]";

		strLog += "(";
		strLog += std::to_string(line);
		strLog += ")";
	}

	if (strLog.empty() == true)
	{
		strLog = strContent;
	}
	else
	{
		strLog.insert(0, strContent);
	}

	strLog.insert(0, strCategory);
	return true;
}

/*
	디버그 출력창에 로그를 출력합니다.
*/
void LoggerInternal::PrintDebugOutputLog(OUT std::string& strLog) const
{
	strLog += "\n";
	::OutputDebugString(strLog.c_str());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
Logger::Logger()
{
	m_pInternal = new LoggerInternal(this);
}

Logger::~Logger()
{
	SAFE_DELETE(m_pInternal);
}

/*
	로거를 초기화합니다.
	콘솔 핸들러 저장과 로그 옵션을 설정합니다.
*/
void Logger::SetUp()
{
	m_pInternal->ActivateOption(EnumIdx::LogOption::TIME);
	m_pInternal->ActivateOption(EnumIdx::LogOption::FILEPATH_AND_LINE);
}

/*
	로거를 정리합니다.
	아직은 추가할 내용이 없어요.
*/
void Logger::CleanUp()
{
	
}

/*
	디버그 모드에서만 출력하는 로그입니다.
*/
void Logger::Trace(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line) const
{
#ifndef _DEBUG
	return;
#endif

	m_pInternal->BeginLog(EConsoleRenderingColor::GREEN);

	std::string strLog;
	if (m_pInternal->MakeLog(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		m_pInternal->EndLog();
		return;
	}

	IConsoleHandler* pConsoleHandler = FIND_SUBSYSTEM(IConsoleHandler);
	pConsoleHandler->RenderString(0, pConsoleHandler->QueryCurrentPosition().Y, strLog.c_str());
	m_pInternal->PrintDebugOutputLog(strLog);

	m_pInternal->EndLog();
}

/*
	디버그 모드에서만 출력하는 로그입니다.
	해당 로그가 출력되면 프로그램을 일시정지합니다.
*/
void Logger::Assert(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line) const
{
#ifndef _DEBUG
	return;
#endif

	m_pInternal->BeginLog(EConsoleRenderingColor::AQUA);

	std::string strLog;
	if (m_pInternal->MakeLog(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		m_pInternal->EndLog();
		return;
	}

	IConsoleHandler* pConsoleHandler = FIND_SUBSYSTEM(IConsoleHandler);
	pConsoleHandler->RenderString(0, pConsoleHandler->QueryCurrentPosition().Y, strLog.c_str());
	m_pInternal->PrintDebugOutputLog(strLog);
	DebugBreak();

	m_pInternal->EndLog();
}

/*
	프로그램 화면과 파일에 출력하는 로그입니다.
*/
void Logger::Info(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line) const
{
	m_pInternal->BeginLog(EConsoleRenderingColor::LIGHT_GREEN);

	std::string strLog;
	if (m_pInternal->MakeLog(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		m_pInternal->EndLog();
		return;
	}

	IConsoleHandler* pConsoleHandler = FIND_SUBSYSTEM(IConsoleHandler);
	pConsoleHandler->RenderString(0, pConsoleHandler->QueryCurrentPosition().Y, strLog.c_str());
	m_pInternal->PrintDebugOutputLog(strLog);

	m_pInternal->EndLog();
}

/*
	프로그램 화면과 파일에 출력하는 로그입니다.
	사용자에게 경고하고 싶을 때 사용합니다.
*/
void Logger::Warning(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line) const
{
	m_pInternal->BeginLog(EConsoleRenderingColor::YELLOW);

	std::string strLog;
	if (m_pInternal->MakeLog(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		m_pInternal->EndLog();
		return;
	}

	IConsoleHandler* pConsoleHandler = FIND_SUBSYSTEM(IConsoleHandler);
	pConsoleHandler->RenderString(0, pConsoleHandler->QueryCurrentPosition().Y, strLog.c_str());
	m_pInternal->PrintDebugOutputLog(strLog);
	DebugBreak();

	m_pInternal->EndLog();
}

/*
	프로그램 화면과 파일에 출력하는 로그입니다.
	에러는 에러코드에 해당되는 내용만 사용할 수 있습니다.
*/
void Logger::Error(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line) const
{
	m_pInternal->BeginLog(EConsoleRenderingColor::LIGHT_YELLOW);

	std::string strLog;
	if (m_pInternal->MakeLog(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		m_pInternal->EndLog();
		return;
	}

	IConsoleHandler* pConsoleHandler = FIND_SUBSYSTEM(IConsoleHandler);
	pConsoleHandler->RenderString(0, pConsoleHandler->QueryCurrentPosition().Y, strLog.c_str());
	m_pInternal->PrintDebugOutputLog(strLog);
	DebugBreak();

	m_pInternal->EndLog();
}

/*
	프로그램 화면과 파일에 출력하는 로그입니다.
	사용자가 확인하면 프로그램을 즉시 종료합니다.
*/
void Logger::Fatal(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line) const
{
	m_pInternal->BeginLog(EConsoleRenderingColor::RED);

	std::string strLog;
	if (m_pInternal->MakeLog(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		m_pInternal->EndLog();
		return;
	}

	IConsoleHandler* pConsoleHandler = FIND_SUBSYSTEM(IConsoleHandler);
	pConsoleHandler->RenderString(0, pConsoleHandler->QueryCurrentPosition().Y, strLog.c_str());
	m_pInternal->PrintDebugOutputLog(strLog);
	m_pInternal->EndLog();

	std::abort();
}