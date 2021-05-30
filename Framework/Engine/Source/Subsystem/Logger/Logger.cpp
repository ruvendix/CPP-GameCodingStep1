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

class InnerPart
{
public:
	InnerPart(Logger* pThis);
	~InnerPart() = default;

	Bool LogImpl(const LogCategoryBase* pCategory, const std::string_view& strContent,
		const Char* szTime, const Char* szFilePath, Int32 line, OUT std::string& strLog);

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
	std::bitset<EnumIdx::LogOption::COUNT> m_bitsetDetail;
};

/*
	�ʿ��� ������ �����մϴ�.
*/
InnerPart::InnerPart(Logger* pThis)
{
	m_pLogger = pThis;
}

/*
	���� �������Դϴ�.
*/
Bool InnerPart::LogImpl(const LogCategoryBase* pCategory, const std::string_view& strContent,
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
	�α׸� ����ϱ� ���� ȣ��˴ϴ�.
*/
void InnerPart::BeginLog(EConsoleRenderingColor renderingColor) const
{
	FIND_SUBSYSTEM(IConsoleHandler)->ChangeRenderingColor(renderingColor, EConsoleRenderingType::TEXT);
}

/*
	�α׸� ����� �Ŀ� ȣ��˴ϴ�.
*/
void InnerPart::EndLog() const
{
	FIND_SUBSYSTEM(IConsoleHandler)->ResetRenderingColor();
}

/*
	���޹��� ���ڵ��� �̿��ؼ� �α� ���ڿ��� ����ϴ�.
*/
Bool InnerPart::MakeLog(const LogCategoryBase* pCategory, const std::string_view& strContent,
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

		// �����ο� ����� �� �� �����Ǿ��ִٸ� �����η� ó���մϴ�.
		if (bAbsoluteFilePath == true)
		{			
			strLog += szFilePath;
		}
		else if (bRelativeFilePath == true)
		{
			strLog += (szFilePath + FrameworkPathfinder::GetFolderPathLength());
		}

		// ������ ���� ��� �ɼ��� Ȱ��ȭ�� ���� ����˴ϴ�.
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
	����� ���â�� �α׸� ����մϴ�.
*/
void InnerPart::PrintDebugOutputLog(OUT std::string& strLog) const
{
	strLog += "\n";
	::OutputDebugString(strLog.c_str());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
Logger::Logger()
{
	m_pInnerPart = new InnerPart(this);
}

Logger::~Logger()
{
	SAFE_DELETE(m_pInnerPart);
}

/*
	�ΰŸ� �ʱ�ȭ�մϴ�.
	�ܼ� �ڵ鷯 ����� �α� �ɼ��� �����մϴ�.
*/
void Logger::SetUp()
{
	m_pInnerPart->ActivateOption(EnumIdx::LogOption::TIME);
	//m_pInnerPart->ActivateOption(EnumIdx::LogOption::ABSOLUTE_FILEPATH);
	m_pInnerPart->ActivateOption(EnumIdx::LogOption::RELATIVE_FILEPATH);
	m_pInnerPart->ActivateOption(EnumIdx::LogOption::LINE);
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

	m_pInnerPart->BeginLog(EConsoleRenderingColor::GREEN);

	std::string strLog;
	if (m_pInnerPart->LogImpl(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		return;
	}

	m_pInnerPart->EndLog();
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

	m_pInnerPart->BeginLog(EConsoleRenderingColor::AQUA);

	std::string strLog;
	if (m_pInnerPart->LogImpl(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		return;
	}

	DebugBreak();
	m_pInnerPart->EndLog();
}

/*
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
*/
void Logger::Info(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line) const
{
	m_pInnerPart->BeginLog(EConsoleRenderingColor::LIGHT_GREEN);

	std::string strLog;
	if (m_pInnerPart->LogImpl(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		return;
	}

	m_pInnerPart->EndLog();
}

/*
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
	����ڿ��� ����ϰ� ���� �� ����մϴ�.
*/
void Logger::Warning(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line) const
{
	m_pInnerPart->BeginLog(EConsoleRenderingColor::YELLOW);

	std::string strLog;
	if (m_pInnerPart->LogImpl(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		return;
	}

	FIND_SUBSYSTEM(IConsoleHandler)->Pause();
	m_pInnerPart->EndLog();
}

/*
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
	������ �����ڵ忡 �ش�Ǵ� ���븸 ����� �� �ֽ��ϴ�.
*/
void Logger::Error(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line) const
{
	m_pInnerPart->BeginLog(EConsoleRenderingColor::LIGHT_YELLOW);

	std::string strLog;
	if (m_pInnerPart->LogImpl(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		return;
	}

	FIND_SUBSYSTEM(IConsoleHandler)->Pause();
	m_pInnerPart->EndLog();
}

/*
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
	����ڰ� Ȯ���ϸ� ���α׷��� ��� �����մϴ�.
*/
void Logger::Fatal(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line) const
{
	m_pInnerPart->BeginLog(EConsoleRenderingColor::RED);

	std::string strLog;
	if (m_pInnerPart->LogImpl(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		return;
	}

	m_pInnerPart->EndLog();
	std::abort();
}