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

#include "BaseLogCategory.h"

class LoggerInside final
{
public:
	LoggerInside(Logger* pOutside)
	{
		m_pOutside = pOutside;
	}

	~LoggerInside() = default;

	Bool DefaultLog(const BaseLogCategory* pCategory, const std::string_view& strContent,
		const Char* szFilePath, Int32 line, OUT std::string& strLog);

	Bool MakeLog(const BaseLogCategory* pCategory, const std::string_view& strContent,
		const Char* szFilePath, Int32 line, OUT std::string& strLog) const;
	
	Bool RenderConsole(EConsoleRenderingColor eRenderingColor, const std::string& strLog);
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
Bool LoggerInside::DefaultLog(const BaseLogCategory* pCategory, const std::string_view& strContent,
	const Char* szFilePath, Int32 line, OUT std::string& strLog)
{
	if (MakeLog(pCategory, strContent, szFilePath, line, strLog) == false)
	{
		return false;
	}

	strLog += "\n";
	::OutputDebugString(strLog.c_str());

	return true;
}

/*
	전달받은 인자들을 이용해서 로그 문자열을 만듭니다.
*/
Bool LoggerInside::MakeLog(const BaseLogCategory* pCategory, const std::string_view& strContent,
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

	ITimeHandler* pTimeHandler = m_pOutside->m_pTimeHandler;
	if ((pTimeHandler != nullptr) &&
		(m_pOutside->IsActivateOption(EnumIdx::LogOption::TIME)))
	{
		std::string strTime;
		pTimeHandler->MakeLocalTimeString(strTime, ':');

		strLog += " [";
		strLog += strTime;
		strLog += "]";
	}

	bool bAbsoluteFilePath = m_pOutside->IsActivateOption(EnumIdx::LogOption::ABSOLUTE_FILEPATH);
	bool bRelativeFilePath = m_pOutside->IsActivateOption(EnumIdx::LogOption::RELATIVE_FILEPATH);
	bool bAnyFilePath = (bAbsoluteFilePath || bRelativeFilePath);

	IFileHandler* pFileHandler = m_pOutside->m_pFileHandler;
	if ((pFileHandler != nullptr) &&
		(bAnyFilePath == true) &&
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
			IPathManager* pPathManager = m_pOutside->m_pPathManager;
			if (pPathManager != nullptr)
			{
				strLog += (szFilePath + pPathManager->FrameworkRelativePathStartPos());
			}
		}

		// 라인은 파일 경로 옵션이 활성화될 때만 적용됩니다.
		if (m_pOutside->IsActivateOption(EnumIdx::LogOption::LINE))
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
	콘솔창에 로그를 출력합니다.
*/
Bool LoggerInside::RenderConsole(EConsoleRenderingColor eRenderingColor, const std::string& strLog)
{
	IConsoleHandler* pConsoleHandler = m_pOutside->m_pConsoleHandler;
	if (pConsoleHandler == nullptr)
	{
		return false;
	}

	if (pConsoleHandler->CheckValidCurrentOutputBuffer() == false)
	{
		return false;
	}

	pConsoleHandler->ChangeRenderingColor(eRenderingColor, EConsoleRenderingType::TEXT);
	pConsoleHandler->ResetRenderingColor();

	return true;
}

/*
	파일에 로그를 출력합니다.
*/
Bool LoggerInside::WriteFile(const std::string_view& strLog)
{
	if (m_pOutside->m_pFileHandler == nullptr)
	{
		return false;
	}

	if (OpenLogFileStream() == false)
	{
		return false;
	}

	std::fprintf(m_pLogFile, strLog.data());

	CloseLogFileStream();
	return true;
}

/*
	로그 파일 스트림을 개방합니다.
*/
Bool LoggerInside::OpenLogFileStream()
{
	EAccessMode accessMode = EAccessMode::UNKNOWN;

	if (m_pLogFile == nullptr)
	{
		IPathManager* pPathManager = m_pOutside->m_pPathManager;
		if (pPathManager == nullptr)
		{
			return false;
		}

		m_strLogFileName = pPathManager->ClientRelativePath() + "Log\\";
		_mkdir(m_strLogFileName.c_str());

		ITimeHandler* pTimeHandler = m_pOutside->m_pTimeHandler;
		if (pPathManager == nullptr)
		{
			return false;
		}
		
		std::string strLocalTime;
		pTimeHandler->MakeLocalTimeString(strLocalTime, '_');
		m_strLogFileName += "[" + strLocalTime + "].log";
		
		accessMode = EAccessMode::WRITE;
	}

	accessMode = EAccessMode::APPEND;

	IFileHandler* pFileHandler = m_pOutside->m_pFileHandler;
	if (pFileHandler == nullptr)
	{
		return false;
	}

	return pFileHandler->OpenFileStream(m_strLogFileName, EFileMode::TEXT, accessMode, &m_pLogFile);
}

/*
	로그 파일 스트림을 닫습니다.
*/
void LoggerInside::CloseLogFileStream()
{
	IFileHandler* pFileHandler = m_pOutside->m_pFileHandler;
	if (pFileHandler != nullptr)
	{
		pFileHandler->CloseFileStream(m_pLogFile);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	로거를 초기화합니다.
	콘솔 핸들러 저장과 로그 옵션을 설정합니다.
*/
void Logger::SetUp()
{
	//ActivateOption(EnumIdx::LogOption::TIME);
	//ActivateOption(EnumIdx::LogOption::ABSOLUTE_FILEPATH);
	//ActivateOption(EnumIdx::LogOption::RELATIVE_FILEPATH);
	//ActivateOption(EnumIdx::LogOption::LINE);

	m_pInside = new LoggerInside(this);
}

/*
	로거를 정리합니다.
*/
void Logger::CleanUp()
{
	SAFE_DELETE(m_pInside);
}

/*
	디버그 모드에서만 출력하는 로그입니다.
*/
void Logger::Trace(const BaseLogCategory* pCategory, const std::string_view& strContent,
	const Char* szFilePath, Int32 line) const
{
	if (m_pInside == nullptr)
	{
		return;
	}

#ifndef _DEBUG
	return;
#endif

	std::string strLog;
	if (m_pInside->DefaultLog(pCategory, strContent, szFilePath, line, strLog) == false)
	{
		return;
	}

	if (m_pInside->RenderConsole(EConsoleRenderingColor::GREEN, strLog) == false)
	{
		return;
	}
}

/*
	디버그 모드에서만 출력하는 로그입니다.
	해당 로그가 출력되면 프로그램을 일시정지합니다.
*/
void Logger::Assert(const BaseLogCategory* pCategory, const std::string_view& strContent,
	const Char* szFilePath, Int32 line) const
{
	if (m_pInside == nullptr)
	{
		return;
	}

#ifndef _DEBUG
	return;
#endif

	std::string strLog;
	if (m_pInside->DefaultLog(pCategory, strContent, szFilePath, line, strLog) == false)
	{
		return;
	}

	if (m_pInside->RenderConsole(EConsoleRenderingColor::AQUA, strLog) == false)
	{
		return;
	}

	DebugBreak();
}

/*
	프로그램 화면과 파일에 출력하는 로그입니다.
*/
void Logger::Info(const BaseLogCategory* pCategory, const std::string_view& strContent,
	const Char* szFilePath, Int32 line) const
{
	if (m_pInside == nullptr)
	{
		return;
	}

	std::string strLog;
	if (m_pInside->DefaultLog(pCategory, strContent, szFilePath, line, strLog) == false)
	{
		return;
	}

	if (m_pInside->RenderConsole(EConsoleRenderingColor::LIGHT_GREEN, strLog) == false)
	{
		return;
	}

	if (m_pInside->WriteFile(strLog) == false)
	{
		return;
	}
}

/*
	프로그램 화면과 파일에 출력하는 로그입니다.
	사용자에게 경고하고 싶을 때 사용합니다.
*/
void Logger::Warning(const BaseLogCategory* pCategory, const std::string_view& strContent,
	const Char* szFilePath, Int32 line) const
{
	if (m_pInside == nullptr)
	{
		return;
	}

	std::string strLog;
	if (m_pInside->DefaultLog(pCategory, strContent, szFilePath, line, strLog) == false)
	{
		return;
	}

	if (m_pInside->RenderConsole(EConsoleRenderingColor::YELLOW, strLog) == false)
	{
		return;
	}

	if (m_pInside->WriteFile(strLog) == false)
	{
		return;
	}

	if (m_pConsoleHandler != nullptr)
	{
		m_pConsoleHandler->Pause();
	}
}

/*
	프로그램 화면과 파일에 출력하는 로그입니다.
	에러는 에러코드에 해당되는 내용만 사용할 수 있습니다.
*/
void Logger::Error(const BaseLogCategory* pCategory, const std::string_view& strContent,
	const Char* szFilePath, Int32 line) const
{
	if (m_pInside == nullptr)
	{
		return;
	}

	std::string strLog;
	if (m_pInside->DefaultLog(pCategory, strContent, szFilePath, line, strLog) == false)
	{
		return;
	}

	if (m_pInside->RenderConsole(EConsoleRenderingColor::LIGHT_YELLOW, strLog) == false)
	{
		return;
	}

	if (m_pInside->WriteFile(strLog) == false)
	{
		return;
	}

	DebugBreak();
}

/*
	프로그램 화면과 파일에 출력하는 로그입니다.
	사용자가 확인하면 프로그램을 즉시 종료합니다.
*/
void Logger::Fatal(const BaseLogCategory* pCategory, const std::string_view& strContent,
	const Char* szFilePath, Int32 line) const
{
	if (m_pInside == nullptr)
	{
		return;
	}

	std::string strLog;
	if (m_pInside->DefaultLog(pCategory, strContent, szFilePath, line, strLog) == false)
	{
		return;
	}

	if (m_pInside->RenderConsole(EConsoleRenderingColor::RED, strLog) == false)
	{
		return;
	}

	if (m_pInside->WriteFile(strLog) == false)
	{
		return;
	}

	std::abort();
}