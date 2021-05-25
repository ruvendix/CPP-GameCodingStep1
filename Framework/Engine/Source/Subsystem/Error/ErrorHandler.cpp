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
	m_mapError.emplace(EErrorCode::UNKNOWN, "알 수 없는 에러!");
	m_mapError.emplace(EErrorCode::INDIRECT_NULLPTR, "nullptr 역참조!");
	m_mapError.emplace(EErrorCode::FAILED_CLEAR_SCREEN, "화면 지우기 실패!");
	m_mapError.emplace(EErrorCode::INVALID_SCREEN_COLOR, "유효하지 않은 화면 색상!");
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
const Char* ErrorHandler::FindErrorContent(EErrorCode errorCode) const
{
	const auto& iter = m_mapError.find(m_lastError);
	if (iter == m_mapError.cend())
	{
		return "";
	}

	return iter->second.c_str();
}