// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������̳� ������ ã�Ƴ� �� ����Ǵ� ���ڿ��� ����� �� ����մϴ�.
// �ܼ�â�Ӹ� �ƴ϶� ���α׷� ȭ�鿡�� �α׸� ����մϴ�. 
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
	���� �������Դϴ�.
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
	���޹��� ���ڵ��� �̿��ؼ� �α� ���ڿ��� ����ϴ�.
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

		// �����ο� ����� �� �� �����Ǿ��ִٸ� �����η� ó���մϴ�.
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

		// ������ ���� ��� �ɼ��� Ȱ��ȭ�� ���� ����˴ϴ�.
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
	�ܼ�â�� �α׸� ����մϴ�.
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
	���Ͽ� �α׸� ����մϴ�.
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
	�α� ���� ��Ʈ���� �����մϴ�.
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
	�α� ���� ��Ʈ���� �ݽ��ϴ�.
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
	�ΰŸ� �ʱ�ȭ�մϴ�.
	�ܼ� �ڵ鷯 ����� �α� �ɼ��� �����մϴ�.
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
	�ΰŸ� �����մϴ�.
*/
void Logger::CleanUp()
{
	SAFE_DELETE(m_pInside);
}

/*
	����� ��忡���� ����ϴ� �α��Դϴ�.
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
	����� ��忡���� ����ϴ� �α��Դϴ�.
	�ش� �αװ� ��µǸ� ���α׷��� �Ͻ������մϴ�.
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
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
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
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
	����ڿ��� ����ϰ� ���� �� ����մϴ�.
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
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
	������ �����ڵ忡 �ش�Ǵ� ���븸 ����� �� �ֽ��ϴ�.
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
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
	����ڰ� Ȯ���ϸ� ���α׷��� ��� �����մϴ�.
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