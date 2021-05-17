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

	void BeginLog(EConsoleRenderingColor renderingColor);
	void EndLog();
	void PrintDebugOutputLog(OUT std::string& strLog);

	Bool MakeLog(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line, OUT std::string& strLog);

	void ActivateOption(EnumIdx::LogOption::Data value)
	{
		m_bitsetDetail.set(value, true);
	}

	bool IsActivateOption(EnumIdx::LogOption::Data value) const
	{
		return m_bitsetDetail.test(value);
	}

	IConsoleHandler* getConsoleHandler() const
	{
		return m_pConsoleHandler;
	}

private:
	Logger* m_pLogger = nullptr;
	IConsoleHandler* m_pConsoleHandler = nullptr;
	std::bitset<EnumIdx::LogOption::END> m_bitsetDetail;
};

/*
	�ʿ��� ������ �����մϴ�.
*/
LoggerInternal::LoggerInternal(Logger* pThis)
{
	m_pLogger = pThis;
	m_pConsoleHandler = ServiceLocator::I().IConsoleHandlerInstance();
}

/*
	�α׸� ����ϱ� ���� ȣ��˴ϴ�.
*/
void LoggerInternal::BeginLog(EConsoleRenderingColor renderingColor)
{
	if (m_pConsoleHandler->ChangeRenderingColor(renderingColor, EConsoleRenderingType::TEXT) == EReturnType::FAIL)
	{
		RX_SIMPLE_ASSERT(nullptr);
		return;
	}
}

/*
	�α׸� ����� �Ŀ� ȣ��˴ϴ�.
*/
void LoggerInternal::EndLog()
{
	m_pConsoleHandler->ResetRenderingColor();
}

/*
	���޹��� ���ڵ��� �̿��ؼ� �α� ���ڿ��� ����ϴ�.
*/
Bool LoggerInternal::MakeLog(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line, OUT std::string& strLog)
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
void LoggerInternal::PrintDebugOutputLog(OUT std::string& strLog)
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
EReturnType Logger::SetUp()
{
	m_pInternal->ActivateOption(EnumIdx::LogOption::TIME);
	m_pInternal->ActivateOption(EnumIdx::LogOption::FILEPATH_AND_LINE);

	return EReturnType::SUCCESS;
}

/*
	�ΰŸ� �����մϴ�.
	������ �߰��� ������ �����.
*/
EReturnType Logger::CleanUp()
{
	return EReturnType::SUCCESS;
}

/*
	�α� ī�װ��� Ȱ��ȭ�մϴ�.
*/
void Logger::ActivateCategory(LogCategoryBase* pCategory)
{
	pCategory->Activate();
}

/*
	�α� ī�װ��� ��Ȱ��ȭ�մϴ�.
*/
void Logger::DeactivateCategory(LogCategoryBase* pCategory)
{
	pCategory->Deactivate();
}

/*
	����� ��忡���� ����ϴ� �α��Դϴ�.
*/
void Logger::Trace(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line)
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

	IConsoleHandler* pConsoleHandler = m_pInternal->getConsoleHandler();
	pConsoleHandler->RenderString(0, pConsoleHandler->QueryCurrentPosition().Y, strLog.c_str());
	m_pInternal->PrintDebugOutputLog(strLog);

	m_pInternal->EndLog();
}

/*
	����� ��忡���� ����ϴ� �α��Դϴ�.
	�ش� �αװ� ��µǸ� ���α׷��� �Ͻ������մϴ�.
*/
void Logger::Assert(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line)
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

	IConsoleHandler* pConsoleHandler = m_pInternal->getConsoleHandler();
	pConsoleHandler->RenderString(0, pConsoleHandler->QueryCurrentPosition().Y, strLog.c_str());
	m_pInternal->PrintDebugOutputLog(strLog);
	DebugBreak();

	m_pInternal->EndLog();
}

/*
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
*/
void Logger::Info(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line)
{
	m_pInternal->BeginLog(EConsoleRenderingColor::LIGHT_GREEN);

	std::string strLog;
	if (m_pInternal->MakeLog(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		m_pInternal->EndLog();
		return;
	}

	IConsoleHandler* pConsoleHandler = m_pInternal->getConsoleHandler();
	pConsoleHandler->RenderString(0, pConsoleHandler->QueryCurrentPosition().Y, strLog.c_str());
	m_pInternal->PrintDebugOutputLog(strLog);

	m_pInternal->EndLog();
}

/*
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
	����ڿ��� ����ϰ� ���� �� ����մϴ�.
*/
void Logger::Warning(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line)
{
	m_pInternal->BeginLog(EConsoleRenderingColor::YELLOW);

	std::string strLog;
	if (m_pInternal->MakeLog(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		m_pInternal->EndLog();
		return;
	}

	IConsoleHandler* pConsoleHandler = m_pInternal->getConsoleHandler();
	pConsoleHandler->RenderString(0, pConsoleHandler->QueryCurrentPosition().Y, strLog.c_str());
	m_pInternal->PrintDebugOutputLog(strLog);

	m_pInternal->EndLog();
}

/*
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
	����ڿ��� ������ �˸��� ���� �� ����մϴ�.
	�߰������� ���� �ڵ忡 �ش�Ǵ� ���� ������ ���Դϴ�.
*/
void Logger::Error(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line)
{
	m_pInternal->BeginLog(EConsoleRenderingColor::LIGHT_YELLOW);

	std::string strLog;
	if (strContent.empty() == true)
	{
		ServiceLocator::I().IErrorHandlerInstance()->FindErrorContent(strLog);
		ServiceLocator::I().IErrorHandlerInstance()->SetLastError(EErrorType::NONE);
	}

	if (m_pInternal->MakeLog(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		m_pInternal->EndLog();
		return;
	}

	IConsoleHandler* pConsoleHandler = m_pInternal->getConsoleHandler();
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
	const Char* szTime, const Char* szFilePath, Int32 line)
{
	m_pInternal->BeginLog(EConsoleRenderingColor::RED);

	std::string strLog;
	if (m_pInternal->MakeLog(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		m_pInternal->EndLog();
		return;
	}

	IConsoleHandler* pConsoleHandler = m_pInternal->getConsoleHandler();
	pConsoleHandler->RenderString(0, pConsoleHandler->QueryCurrentPosition().Y, strLog.c_str());
	m_pInternal->PrintDebugOutputLog(strLog);
	m_pInternal->EndLog();

	std::abort();
}