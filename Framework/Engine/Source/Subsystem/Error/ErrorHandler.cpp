// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 마지막에 발생된 에러에 해당되는 내용을 알려줍니다.
// 에러가 발생되자마자 에러 핸들러가 작동됩니다.
// =====================================================================================
#include "EnginePCH.h"
#include "ErrorHandler.h"

/*
	에러 핸들러를 초기화합니다.
	에러 타입에 해당되는 에러 내용을 설정해요.
*/
void ErrorHandler::SetUp()
{
	m_mapError.insert(std::make_pair(EErrorType::INDIRECT_NULLPTR, "nullptr 역참조 에러!"));

	
}

/*
	에러 핸들러를 정리합니다.
	아직은 추가할 내용이 없어요.
*/
void ErrorHandler::CleanUp()
{
	
}

/*
	마지막에 발생된 에러에 해당되는 내용을 가져옵니다.
*/
void ErrorHandler::FindErrorContent(OUT std::string& strError)
{
	const auto& iter = m_mapError.find(m_lastError);
	if (iter != m_mapError.cend())
	{
		strError = iter->second;
	}
}

/*
	마지막에 발생된 에러를 기록합니다.
*/
void ErrorHandler::SetLastError(EErrorType error)
{
	m_lastError = error;
}