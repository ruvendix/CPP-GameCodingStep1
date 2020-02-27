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

DEFINE_LOG_CATEGORY(ErrorHandler);

/*
에러 타입에 따라 에러 내용을 보여줍니다.
*/
void ErrorHandler::ShowString(EErrorType errorType)
{
	switch (errorType)
	{
		CASE_LOG_BREAK(EErrorType::INIT_FAILED, "초기화 실패!");
		CASE_LOG_BREAK(EErrorType::UPDATE_FAILED, "갱신 실패!");
		CASE_LOG_BREAK(EErrorType::RENDER_FAILED, "렌더링 실패!");
		CASE_LOG_BREAK(EErrorType::FINAL_FAILED, "마무리 실패!");

		CASE_LOG_BREAK(EErrorType::UNKNOWN_CONSOLE_SCREEN_BUFFER_TYPE, "알 수 없는 콘솔 스크린 버퍼!");
		CASE_LOG_BREAK(EErrorType::UNKNOWN_CONSOLE_COLOR, "알 수 없는 콘솔 색상!");
		CASE_LOG_BREAK(EErrorType::UNKNOWN_CONSOLE_OUTPUT_TYPE, "알 수 없는 콘솔 출력 타입!");
		CASE_LOG_BREAK(EErrorType::UNKNOWN_INTRO_MENU_SCENE_LOADER_TYPE, "알 수 없는 인트로 메뉴 씬 로더 타입!");
		CASE_LOG_BREAK(EErrorType::UNKNOWN_FRAME_RATE_TYPE, "알 수 없는 프레임 레이트 타입!");

		CASE_LOG_BREAK(EErrorType::NO_FRAME_LIMITED_ON_UNLIMITED_FRAME_RATE, "무제한 프레임 레이트에서는 프레임 제한을 걸 수 없음!");
		CASE_LOG_BREAK(EErrorType::INPUT_MAPPING_VAL_IS_ONLY_UPPERCASE, "입력 매핑 입력값은 대문자만 가능!");
		CASE_LOG_BREAK(EErrorType::INPUT_MAPPING_SECOND_ARG_IS_NOT_AVAILABLE_STRING, "입력 매핑 입력값의 두 번째 인자는 문자열이 될 수 없음!");
	}

	__debugbreak();
}

/*
에러 타입에 해당되는 문자열을 미리 조합한 문자열로 보여줍니다.
*/
void ErrorHandler::ShowFormatString(const std::string_view& szError)
{
	DEBUG_LOG_CATEGORY(ErrorHandler, szError.data());
	__debugbreak();
}

/*
에러 타입에 따라 서식 문자열을 반환합니다.
*/
std::string_view ErrorHandler::ToFormatString(EErrorType errorType)
{
	switch (errorType)
	{
		CASE_RETURN_STRING(EErrorType::NULLPTR, "(%s)가 널포인터인 상태에서 역참조!");
		CASE_RETURN_STRING(EErrorType::NO_INPUT_MAPPING_INFO, "입력 매핑 목록에 (%s)에 해당되는 정보가 없음!");
		CASE_RETURN_STRING(EErrorType::NO_PERFORMANCE_PROFILE_INFO, "프로파일 목록에 (%d)에 해당되는 정보가 없음!");
		CASE_RETURN_STRING(EErrorType::OVERLAPPED_SCENE, "(%s) 씬은 이미 등록되어있음!");
	}

	return "등록된 에러 서식 문자열이 없음!";
}
