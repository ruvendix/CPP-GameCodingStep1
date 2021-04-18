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
	로거를 초기화합니다.
	콘솔 핸들러 저장과 로그 옵션을 설정합니다.
*/
EReturnType Logger::SetUp()
{
	pConsoleHandler = ServiceLocator::I().IConsoleHandlerInstance();

	detailOption.set(ToUnderlyingType(EDetailType::TIME), true);
	detailOption.set(ToUnderlyingType(EDetailType::FILEPATH_AND_LINE), true);

	return EReturnType::SUCCESS;
}

/*
	로거를 정리합니다.
	아직은 추가할 내용이 없어요.
*/
EReturnType Logger::CleanUp()
{
	return EReturnType::SUCCESS;
}

/*
	로그 카테고리를 활성화합니다.
*/
void Logger::ActivateCategory(LogCategoryBase* pCategory)
{
	pCategory->Activate();
}

/*
	로그 카테고리를 비활성화합니다.
*/
void Logger::DeactivateCategory(LogCategoryBase* pCategory)
{
	pCategory->Deactivate();
}

/*
	디버그 모드에서만 출력하는 로그입니다.
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
	디버그 모드에서만 출력하는 로그입니다.
	해당 로그가 출력되면 프로그램을 일시정지합니다.
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
	프로그램 화면과 파일에 출력하는 로그입니다.
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
	프로그램 화면과 파일에 출력하는 로그입니다.
	사용자에게 경고하고 싶을 때 사용합니다.
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
	프로그램 화면과 파일에 출력하는 로그입니다.
	사용자에게 에러로 알리고 싶을 때 사용합니다.
	추가적으로 에러 코드에 해당되는 에러 내용을 붙입니다.
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
	프로그램 화면과 파일에 출력하는 로그입니다.
	사용자가 확인하면 프로그램을 즉시 종료합니다.
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
		로그를 출력하기 전에 호출됩니다.
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
		로그를 출력한 후에 호출됩니다.
	*/
	void EndLog()
	{
		pConsoleHandler->ResetRenderingColor();
	}

	/*
		전달받은 인자들을 이용해서 로그 문자열을 만듭니다.
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
		디버그 출력창에 로그를 출력합니다.
	*/
	void PrintDebugOutputLog(OUT std::string& strLog)
	{
		strLog += "\n";
		::OutputDebugString(strLog.c_str());
	}
}