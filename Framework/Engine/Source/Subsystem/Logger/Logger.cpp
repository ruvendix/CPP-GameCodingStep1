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

class LoggerInside
{
public:
	LoggerInside() = default;
	~LoggerInside() = default;

	Bool LogImpl(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line, OUT std::string& strLog);

	void BeginLog(EConsoleRenderingColor eRenderingColor) const;
	void EndLog() const;
	void PrintDebugOutputLog(OUT std::string& strLog) const;

	Bool MakeLog(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line, OUT std::string& strLog) const;

	bool IsActivateOption(EnumIdx::LogOption::Data value) const { return m_bitsetDetail.test(value); }

	void ActivateOption(EnumIdx::LogOption::Data value) { m_bitsetDetail.set(value, true); }
	void DeactivateOption(EnumIdx::LogOption::Data value) { m_bitsetDetail.set(value, false); }

private:
	std::bitset<EnumIdx::LogOption::COUNT> m_bitsetDetail;
};

/*
	공통 구현부입니다.
*/
Bool LoggerInside::LogImpl(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line, OUT std::string& strLog)
{
	if (MakeLog(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		EndLog();
		return false;
	}

	IConsoleHandler* pConsoleHandler = FIND_SUBSYSTEM(IConsoleHandler);
	pConsoleHandler->RenderString(0, pConsoleHandler->QueryCurrentPosition().Y, strLog.c_str());
	PrintDebugOutputLog(strLog);

	return true;
}

/*
	로그를 출력하기 전에 호출됩니다.
*/
void LoggerInside::BeginLog(EConsoleRenderingColor eRenderingColor) const
{
	FIND_SUBSYSTEM(IConsoleHandler)->ChangeRenderingColor(eRenderingColor, EConsoleRenderingType::TEXT);
}

/*
	로그를 출력한 후에 호출됩니다.
*/
void LoggerInside::EndLog() const
{
	FIND_SUBSYSTEM(IConsoleHandler)->ResetRenderingColor();
}

/*
	전달받은 인자들을 이용해서 로그 문자열을 만듭니다.
*/
Bool LoggerInside::MakeLog(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line, OUT std::string& strLog) const
{
	std::string strCategory;
	if (pCategory != nullptr)
	{
		if (pCategory->CheckActivate() == false)
		{
			return false;
		}

		strCategory = pCategory->GetName() + ": ";
	}

	if ((IsActivateOption(EnumIdx::LogOption::TIME)) &&
		(szTime != 0))
	{
		strLog += " [";
		strLog += szTime;
		strLog += "]";
	}

	bool bAbsoluteFilePath = IsActivateOption(EnumIdx::LogOption::ABSOLUTE_FILEPATH);
	bool bRelativeFilePath = IsActivateOption(EnumIdx::LogOption::RELATIVE_FILEPATH);
	bool bAnyFilePath = (bAbsoluteFilePath || bRelativeFilePath);

	if ((bAnyFilePath == true) &&
		(szFilePath != nullptr))
	{
		strLog += " [";

		// 절대경로와 상대경로 둘 다 설정되어있다면 절대경로로 처리합니다.
		if (bAbsoluteFilePath == true)
		{			
			strLog += szFilePath;
		}
		else if (bRelativeFilePath == true)
		{
			strLog += (szFilePath + FrameworkPathfinder::GetFolderPathLength());
		}

		// 라인은 파일 경로 옵션이 활성화될 때만 적용됩니다.
		if (IsActivateOption(EnumIdx::LogOption::LINE))
		{
			strLog += "(";
			strLog += std::to_string(line);
			strLog += ")";
		}

		strLog += "]";
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
void LoggerInside::PrintDebugOutputLog(OUT std::string& strLog) const
{
	strLog += "\n";
	::OutputDebugString(strLog.c_str());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
Logger::Logger()
{
	m_spLoggerInside = std::make_unique<LoggerInside>();
}

/*
	로거를 초기화합니다.
	콘솔 핸들러 저장과 로그 옵션을 설정합니다.
*/
void Logger::SetUp()
{
	m_spLoggerInside->ActivateOption(EnumIdx::LogOption::TIME);
	//m_spLoggerInside->ActivateOption(EnumIdx::LogOption::ABSOLUTE_FILEPATH);
	m_spLoggerInside->ActivateOption(EnumIdx::LogOption::RELATIVE_FILEPATH);
	m_spLoggerInside->ActivateOption(EnumIdx::LogOption::LINE);
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

	m_spLoggerInside->BeginLog(EConsoleRenderingColor::GREEN);

	std::string strLog;
	if (m_spLoggerInside->LogImpl(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		return;
	}

	m_spLoggerInside->EndLog();
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

	m_spLoggerInside->BeginLog(EConsoleRenderingColor::AQUA);

	std::string strLog;
	if (m_spLoggerInside->LogImpl(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		return;
	}

	DebugBreak();
	m_spLoggerInside->EndLog();
}

/*
	프로그램 화면과 파일에 출력하는 로그입니다.
*/
void Logger::Info(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line) const
{
	m_spLoggerInside->BeginLog(EConsoleRenderingColor::LIGHT_GREEN);

	std::string strLog;
	if (m_spLoggerInside->LogImpl(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		return;
	}

	m_spLoggerInside->EndLog();
}

/*
	프로그램 화면과 파일에 출력하는 로그입니다.
	사용자에게 경고하고 싶을 때 사용합니다.
*/
void Logger::Warning(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line) const
{
	m_spLoggerInside->BeginLog(EConsoleRenderingColor::YELLOW);

	std::string strLog;
	if (m_spLoggerInside->LogImpl(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		return;
	}

	FIND_SUBSYSTEM(IConsoleHandler)->Pause();
	m_spLoggerInside->EndLog();
}

/*
	프로그램 화면과 파일에 출력하는 로그입니다.
	에러는 에러코드에 해당되는 내용만 사용할 수 있습니다.
*/
void Logger::Error(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line) const
{
	m_spLoggerInside->BeginLog(EConsoleRenderingColor::LIGHT_YELLOW);

	std::string strLog;
	if (m_spLoggerInside->LogImpl(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		return;
	}

	FIND_SUBSYSTEM(IConsoleHandler)->Pause();
	m_spLoggerInside->EndLog();
}

/*
	프로그램 화면과 파일에 출력하는 로그입니다.
	사용자가 확인하면 프로그램을 즉시 종료합니다.
*/
void Logger::Fatal(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line) const
{
	m_spLoggerInside->BeginLog(EConsoleRenderingColor::RED);

	std::string strLog;
	if (m_spLoggerInside->LogImpl(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		return;
	}

	m_spLoggerInside->EndLog();
	std::abort();
}