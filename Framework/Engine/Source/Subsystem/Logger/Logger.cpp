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

class LoggerInside final
{
public:
	LoggerInside(Logger* pOutside)
	{
		m_pOutside = pOutside;
	}

	~LoggerInside() = default;

	Bool LogImpl(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szFilePath, Int32 line, OUT std::string& strLog);

	Bool BeginLog(EConsoleRenderingColor eRenderingColor) const;
	void EndLog() const;
	void PrintDebugOutputLog(OUT std::string& strLog) const;

	Bool MakeLog(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szFilePath, Int32 line, OUT std::string& strLog) const;

	Bool WriteFile(const std::string_view& strLog);

	Bool OpenLogFileStream();
	void CloseLogFileStream();

private:
	Logger* m_pOutside = nullptr;

	FILE* m_pLogFile = nullptr;
	std::string m_strLogFileName;	
};

/*
	공통 구현부입니다.
*/
Bool LoggerInside::LogImpl(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szFilePath, Int32 line, OUT std::string& strLog)
{
	if (MakeLog(pCategory, strContent, szFilePath, line, strLog) == false)
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
Bool LoggerInside::BeginLog(EConsoleRenderingColor eRenderingColor) const
{
	if (FIND_SUBSYSTEM(IConsoleHandler)->CheckValidCurrentOutputBuffer() == false)
	{
		return false;
	}

	FIND_SUBSYSTEM(IConsoleHandler)->ChangeRenderingColor(eRenderingColor, EConsoleRenderingType::TEXT);
	return true;
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
	const Char* szFilePath, Int32 line, OUT std::string& strLog) const
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

	Logger::DataPtr spData = m_pOutside->Data();
	if (spData->IsActivateOption(EnumIdx::LogOption::TIME))
	{
		std::string strTime;
		FIND_SUBSYSTEM(ITimeHandler)->MakeLocalTimeString(strTime, ':');

		strLog += " [";
		strLog += strTime;
		strLog += "]";
	}

	bool bAbsoluteFilePath = spData->IsActivateOption(EnumIdx::LogOption::ABSOLUTE_FILEPATH);
	bool bRelativeFilePath = spData->IsActivateOption(EnumIdx::LogOption::RELATIVE_FILEPATH);
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
			strLog += (szFilePath + FIND_SUBSYSTEM(IPathManager)->FrameworkRelativePathStartPos());
		}

		// 라인은 파일 경로 옵션이 활성화될 때만 적용됩니다.
		if (spData->IsActivateOption(EnumIdx::LogOption::LINE))
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

Bool LoggerInside::WriteFile(const std::string_view& strLog)
{
	if (OpenLogFileStream() == false)
	{
		return false;
	}

	std::fprintf(m_pLogFile, strLog.data());

	CloseLogFileStream();
	return true;
}

Bool LoggerInside::OpenLogFileStream()
{
	EAccessMode accessMode = EAccessMode::UNKNOWN;

	if (m_pLogFile == nullptr)
	{
		m_strLogFileName = FIND_SUBSYSTEM(IPathManager)->ClientRelativePath() + "Log\\";
		_mkdir(m_strLogFileName.c_str());
		
		std::string strLocalTime;
		FIND_SUBSYSTEM(ITimeHandler)->MakeLocalTimeString(strLocalTime, '_');
		m_strLogFileName += "[" + strLocalTime + "].log";
		
		accessMode = EAccessMode::WRITE;
	}

	accessMode = EAccessMode::APPEND;
	return FIND_SUBSYSTEM(IFileHandler)->OpenFileStream(m_strLogFileName, EFileMode::TEXT, accessMode, &m_pLogFile);
}

void LoggerInside::CloseLogFileStream()
{
	FIND_SUBSYSTEM(IFileHandler)->CloseFileStream(m_pLogFile);
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
	m_spInside = std::make_unique<LoggerInside>(this);
}

/*
	로거를 초기화합니다.
	콘솔 핸들러 저장과 로그 옵션을 설정합니다.
*/
void Logger::SetUp()
{
	DataPtr spData = Data();
	spData->ActivateOption(EnumIdx::LogOption::TIME);
	spData->ActivateOption(EnumIdx::LogOption::ABSOLUTE_FILEPATH);
	spData->ActivateOption(EnumIdx::LogOption::RELATIVE_FILEPATH);
	spData->ActivateOption(EnumIdx::LogOption::LINE);
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
	const Char* szFilePath, Int32 line) const
{
#ifndef _DEBUG
	return;
#endif

	if (m_spInside->BeginLog(EConsoleRenderingColor::GREEN) == false)
	{
		return;
	}

	std::string strLog;
	if (m_spInside->LogImpl(pCategory, strContent, szFilePath, line, strLog) == false)
	{
		return;
	}

	m_spInside->EndLog();
}

/*
	디버그 모드에서만 출력하는 로그입니다.
	해당 로그가 출력되면 프로그램을 일시정지합니다.
*/
void Logger::Assert(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szFilePath, Int32 line) const
{
#ifndef _DEBUG
	return;
#endif

	if (m_spInside->BeginLog(EConsoleRenderingColor::AQUA) == false)
	{
		return;
	}

	std::string strLog;
	if (m_spInside->LogImpl(pCategory, strContent, szFilePath, line, strLog) == false)
	{
		return;
	}

	DebugBreak();
	m_spInside->EndLog();
}

/*
	프로그램 화면과 파일에 출력하는 로그입니다.
*/
void Logger::Info(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szFilePath, Int32 line) const
{
	if (m_spInside->BeginLog(EConsoleRenderingColor::LIGHT_GREEN) == false)
	{
		return;
	}

	std::string strLog;
	if (m_spInside->LogImpl(pCategory, strContent, szFilePath, line, strLog) == false)
	{
		return;
	}

	m_spInside->EndLog();
	m_spInside->WriteFile(strLog);
}

/*
	프로그램 화면과 파일에 출력하는 로그입니다.
	사용자에게 경고하고 싶을 때 사용합니다.
*/
void Logger::Warning(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szFilePath, Int32 line) const
{
	if (m_spInside->BeginLog(EConsoleRenderingColor::YELLOW) == false)
	{
		return;
	}

	std::string strLog;
	if (m_spInside->LogImpl(pCategory, strContent, szFilePath, line, strLog) == false)
	{
		return;
	}

	FIND_SUBSYSTEM(IConsoleHandler)->Pause();
	m_spInside->EndLog();
	m_spInside->WriteFile(strLog);
}

/*
	프로그램 화면과 파일에 출력하는 로그입니다.
	에러는 에러코드에 해당되는 내용만 사용할 수 있습니다.
*/
void Logger::Error(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szFilePath, Int32 line) const
{
	if (m_spInside->BeginLog(EConsoleRenderingColor::LIGHT_YELLOW) == false)
	{
		return;
	}

	std::string strLog;
	if (m_spInside->LogImpl(pCategory, strContent, szFilePath, line, strLog) == false)
	{
		return;
	}

	DebugBreak();
	m_spInside->EndLog();
	m_spInside->WriteFile(strLog);
}

/*
	프로그램 화면과 파일에 출력하는 로그입니다.
	사용자가 확인하면 프로그램을 즉시 종료합니다.
*/
void Logger::Fatal(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szFilePath, Int32 line) const
{
	if (m_spInside->BeginLog(EConsoleRenderingColor::RED) == false)
	{
		return;
	}

	std::string strLog;
	if (m_spInside->LogImpl(pCategory, strContent, szFilePath, line, strLog) == false)
	{
		return;
	}

	m_spInside->EndLog();
	m_spInside->WriteFile(strLog);

	std::abort();
}