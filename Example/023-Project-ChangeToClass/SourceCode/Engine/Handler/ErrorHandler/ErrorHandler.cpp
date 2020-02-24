// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� Ÿ�Կ� ���� ó�����ִ� �ڵ鷯�Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "ErrorHandler.h"

DEFINE_LOG_CATEGORY(ErrorHandler);

#define CASE_ERROR_STRING(errorType, szError)\
	case errorType:\
	{\
		DEBUG_LOG_CATEGORY(ErrorHandler, szError);\
		break;\
	}

#define CASE_ERROR_FORMAT_STRING(errorType, szErrorFormat)\
	case errorType:\
	{\
		return szErrorFormat;\
	}

/*
���� Ÿ�Կ� ���� ���� ������ �����ݴϴ�.
*/
void ErrorHandler::ShowErrorString(EErrorType errorType)
{
	switch (errorType)
	{
		CASE_ERROR_STRING(EErrorType::INIT_FAILED, "�ʱ�ȭ ����!");
		CASE_ERROR_STRING(EErrorType::UPDATE_FAILED, "���� ����!");
		CASE_ERROR_STRING(EErrorType::RENDER_FAILED, "������ ����!");
		CASE_ERROR_STRING(EErrorType::FINAL_FAILED, "������ ����!");

		CASE_ERROR_STRING(EErrorType::UNKNOWN_CONSOLE_SCREEN_BUFFER_TYPE, "�� �� ���� �ܼ� ��ũ�� ����!");
		CASE_ERROR_STRING(EErrorType::UNKNOWN_CONSOLE_COLOR, "�� �� ���� �ܼ� ����!");
		CASE_ERROR_STRING(EErrorType::UNKNOWN_CONSOLE_OUTPUT_TYPE, "�� �� ���� �ܼ� ��� Ÿ��!");

		CASE_ERROR_STRING(EErrorType::NO_FRAME_LIMITED_ON_UNLIMITED_FRAME_RATE, "������ ������ ����Ʈ������ ������ ������ �� �� ����!");
		CASE_ERROR_STRING(EErrorType::INPUT_MAPPING_VAL_IS_ONLY_UPPERCASE, "�Է� ���� �Է°��� �빮�ڸ� ����!");
		CASE_ERROR_STRING(EErrorType::INPUT_MAPPING_SECOND_ARG_IS_NOT_AVAILABLE_STRING, "�Է� ���� �Է°��� �� ��° ���ڴ� ���ڿ��� �� �� ����!");
	}

	__debugbreak();
}

/*
���� Ÿ�Կ� �ش�Ǵ� ���ڿ��� �̸� ������ ���ڿ��� �����ݴϴ�.
*/
void ErrorHandler::ShowErrorFormatString(const std::string_view& szError)
{
	DEBUG_LOG_CATEGORY(ErrorHandler, szError.data());
	__debugbreak();
}

/*
���� Ÿ�Կ� ���� ���� ���ڿ��� ��ȯ�մϴ�.
*/
std::string_view ErrorHandler::GetErrorFormatString(EErrorType errorType)
{
	switch (errorType)
	{
		CASE_ERROR_FORMAT_STRING(EErrorType::NULLPTR, "(%s)�� ���������� ���¿��� ������!");
		CASE_ERROR_FORMAT_STRING(EErrorType::NO_INPUT_MAPPING_INFO, "�Է� ���� ��Ͽ� (%s)�� �ش�Ǵ� ������ ����!");
		CASE_ERROR_FORMAT_STRING(EErrorType::NO_PERFORMANCE_PROFILE_INFO, "�������� ��Ͽ� (%d)�� �ش�Ǵ� ������ ����!");
		CASE_ERROR_FORMAT_STRING(EErrorType::OVERLAPPED_SCENE, "(%s) ���� �̹� ��ϵǾ�����!");
	}

	return "��ϵ� ���� ���� ���ڿ��� ����!";
}
