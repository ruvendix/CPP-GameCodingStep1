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

namespace
{
	IConsoleHandler* pConsoleHandler = nullptr;
	std::bitset<ToUnderlyingType(EDetailType::COUNT)> detailOption;

	void BeginLog(EConsoleRenderingColor renderingColor);
	void EndLog();
	void PrintDebugOutputLog(OUT std::string& strLog);

	Bool MakeLog(const LogCategoryBase* pCategory, const std::string_view& strContent,
		 const Char* szTime, const Char* szFilePath, Int32 line, OUT std::string& strLog);	
}

/*
	�ΰŸ� �ʱ�ȭ�մϴ�.
	�ܼ� �ڵ鷯 ����� �α� �ɼ��� �����մϴ�.
*/
EReturnType Logger::SetUp()
{
	pConsoleHandler = ServiceLocator::I().IConsoleHandlerInstance();

	detailOption.set(ToUnderlyingType(EDetailType::TIME), true);
	detailOption.set(ToUnderlyingType(EDetailType::FILEPATH_AND_LINE), true);

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

	BeginLog(EConsoleRenderingColor::GREEN);

	std::string strLog;
	if (MakeLog(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		EndLog();
		return;
	}

	pConsoleHandler->RenderString(0, pConsoleHandler->QueryCurrentPosition().Y, strLog.c_str());
	PrintDebugOutputLog(strLog);

	EndLog();
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

	BeginLog(EConsoleRenderingColor::AQUA);

	std::string strLog;
	if (MakeLog(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		EndLog();
		return;
	}

	pConsoleHandler->RenderString(0, pConsoleHandler->QueryCurrentPosition().Y, strLog.c_str());
	PrintDebugOutputLog(strLog);
	DebugBreak();

	EndLog();
}

/*
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
*/
void Logger::Info(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line)
{
	BeginLog(EConsoleRenderingColor::LIGHT_GREEN);

	std::string strLog;
	if (MakeLog(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		EndLog();
		return;
	}

	pConsoleHandler->RenderString(0, pConsoleHandler->QueryCurrentPosition().Y, strLog.c_str());
	PrintDebugOutputLog(strLog);

	EndLog();
}

/*
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
	����ڿ��� ����ϰ� ���� �� ����մϴ�.
*/
void Logger::Warning(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line)
{
	BeginLog(EConsoleRenderingColor::YELLOW);

	std::string strLog;
	if (MakeLog(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		EndLog();
		return;
	}

	pConsoleHandler->RenderString(0, pConsoleHandler->QueryCurrentPosition().Y, strLog.c_str());
	PrintDebugOutputLog(strLog);

	EndLog();
}

/*
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
	����ڿ��� ������ �˸��� ���� �� ����մϴ�.
	�߰������� ���� �ڵ忡 �ش�Ǵ� ���� ������ ���Դϴ�.
*/
void Logger::Error(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line)
{
	BeginLog(EConsoleRenderingColor::LIGHT_YELLOW);

	std::string strLog;
	if (MakeLog(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		EndLog();
		return;
	}

	pConsoleHandler->RenderString(0, pConsoleHandler->QueryCurrentPosition().Y, strLog.c_str());
	PrintDebugOutputLog(strLog);

	EndLog();
}

/*
	���α׷� ȭ��� ���Ͽ� ����ϴ� �α��Դϴ�.
	����ڰ� Ȯ���ϸ� ���α׷��� ��� �����մϴ�.
*/
void Logger::Fatal(const LogCategoryBase* pCategory, const std::string_view& strContent,
	const Char* szTime, const Char* szFilePath, Int32 line)
{
	BeginLog(EConsoleRenderingColor::RED);

	std::string strLog;
	if (MakeLog(pCategory, strContent, szTime, szFilePath, line, strLog) == false)
	{
		EndLog();
		return;
	}

	::OutputDebugString(strLog.c_str());
	pConsoleHandler->RenderString(0, pConsoleHandler->QueryCurrentPosition().Y, strLog.c_str());
	std::abort();

	EndLog();
}

namespace
{
	/*
		�α׸� ����ϱ� ���� ȣ��˴ϴ�.
	*/
	void BeginLog(EConsoleRenderingColor renderingColor)
	{
		if (pConsoleHandler->ChangeRenderingColor(renderingColor, EConsoleRenderingType::TEXT) == EReturnType::FAIL)
		{
			assert(nullptr);
			return;
		}
	}

	/*
		�α׸� ����� �Ŀ� ȣ��˴ϴ�.
	*/
	void EndLog()
	{
		pConsoleHandler->ResetRenderingColor();
	}

	/*
		���޹��� ���ڵ��� �̿��ؼ� �α� ���ڿ��� ����ϴ�.
	*/
	Bool MakeLog(const LogCategoryBase* pCategory, const std::string_view& strContent,
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

		if ((detailOption.test(ToUnderlyingType(EDetailType::TIME)) == true) &&
			(szTime != nullptr))
		{
			strLog += " [";
			strLog += szTime;
			strLog += "]";
		}

		if ((detailOption.test(ToUnderlyingType(EDetailType::FILEPATH_AND_LINE)) == true) &&
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
	void PrintDebugOutputLog(OUT std::string& strLog)
	{
		strLog += "\n";
		::OutputDebugString(strLog.c_str());
	}
}