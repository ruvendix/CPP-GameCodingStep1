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
	���� �������Դϴ�.
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
	�α׸� ����ϱ� ���� ȣ��˴ϴ�.
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
	�α׸� ����� �Ŀ� ȣ��˴ϴ�.
*/
void LoggerInside::EndLog() const
{
	FIND_SUBSYSTEM(IConsoleHandler)->ResetRenderingColor();
}

/*
	���޹��� ���ڵ��� �̿��ؼ� �α� ���ڿ��� ����ϴ�.
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

		// �����ο� ����� �� �� �����Ǿ��ִٸ� �����η� ó���մϴ�.
		if (bAbsoluteFilePath == true)
		{			
			strLog += szFilePath;
		}
		else if (bRelativeFilePath == true)
		{
			strLog += (szFilePath + FIND_SUBSYSTEM(IPathManager)->FrameworkRelativePathStartPos());
		}

		// ������ ���� ��� �ɼ��� Ȱ��ȭ�� ���� ����˴ϴ�.
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
	����� ���â�� �α׸� ����մϴ�.
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
	�ΰŸ� �ʱ�ȭ�մϴ�.
	�ܼ� �ڵ鷯 ����� �α� �ɼ��� �����մϴ�.
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
	�ΰŸ� �����մϴ�.
	������ �߰��� ������ �����.
*/
void Logger::CleanUp()
{
	
}

/*
	����� ��忡���� ����ϴ� �α��Դϴ�.
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
	����� ��忡���� ����ϴ� �α��Դϴ�.
	�ش� �αװ� ��µǸ� ���α׷��� �Ͻ������մϴ�.
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
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
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
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
	����ڿ��� ����ϰ� ���� �� ����մϴ�.
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
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
	������ �����ڵ忡 �ش�Ǵ� ���븸 ����� �� �ֽ��ϴ�.
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
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
	����ڰ� Ȯ���ϸ� ���α׷��� ��� �����մϴ�.
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