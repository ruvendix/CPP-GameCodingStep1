// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 에러 타입에 따라 처리해주는 핸들러입니다.
// =====================================================================================

#include "PCH.h"
#include "ErrorHandler.h"

#define CASE_ERROR_STRING(errorType, szError)\
	case errorType:\
	{\
		DEBUG_LOG(szError);\
		break;\
	}

/*
에러 타입에 따라 에러 내용을 보여줍니다.
*/
void ErrorHandler::ShowError(EErrorType errorType)
{
	switch (errorType)
	{
	CASE_ERROR_STRING(EErrorType::INIT_FAILED, "초기화 실패!");
	CASE_ERROR_STRING(EErrorType::UPDATE_FAILED, "갱신 실패!");
	CASE_ERROR_STRING(EErrorType::RENDER_FAILED, "렌더링 실패!");
	CASE_ERROR_STRING(EErrorType::FINAL_FAILED, "마무리 실패!");
	}
}
