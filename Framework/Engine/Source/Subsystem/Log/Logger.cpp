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
	�ʿ��� ������ �����մϴ�.
*/
LoggerInternal::LoggerInternal(Logger* pThis)
{
	m_pLogger = pThis;
}

/*
	�α׸� ����ϱ� ���� ȣ��˴ϴ�.
*/
void LoggerInternal::BeginLog(EConsoleRenderingColor renderingColor) const
{
	FIND_SUBSYSTEM(IConsoleHandler)->ChangeRenderingColor(renderingColor, EConsoleRenderingType::TEXT);
}

/*
	�α׸� ����� �Ŀ� ȣ��˴ϴ�.
*/
void LoggerInternal::EndLog() const
{
	FIND_SUBSYSTEM(IConsoleHandler)->ResetRenderingColor();
}

/*
	���޹��� ���ڵ��� �̿��ؼ� �α� ���ڿ��� ����ϴ�.
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
	����� ���â�� �α׸� ����մϴ�.
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
	�ΰŸ� �ʱ�ȭ�մϴ�.
	�ܼ� �ڵ鷯 ����� �α� �ɼ��� �����մϴ�.
*/
void Logger::SetUp()
{
	m_pInternal->ActivateOption(EnumIdx::LogOption::TIME);
	m_pInternal->ActivateOption(EnumIdx::LogOption::FILEPATH_AND_LINE);
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
	����� ��忡���� ����ϴ� �α��Դϴ�.
	�ش� �αװ� ��µǸ� ���α׷��� �Ͻ������մϴ�.
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
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
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
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
	����ڿ��� ����ϰ� ���� �� ����մϴ�.
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
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
	������ �����ڵ忡 �ش�Ǵ� ���븸 ����� �� �ֽ��ϴ�.
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
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
	����ڰ� Ȯ���ϸ� ���α׷��� ��� �����մϴ�.
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