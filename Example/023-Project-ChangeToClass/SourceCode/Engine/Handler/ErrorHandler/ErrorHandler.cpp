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

/*
���� Ÿ�Կ� ���� ���� ������ �����ݴϴ�.
*/
void ErrorHandler::ShowString(EErrorType errorType)
{
	switch (errorType)
	{
		CASE_LOG_BREAK(EErrorType::INIT_FAILED, "�ʱ�ȭ ����!");
		CASE_LOG_BREAK(EErrorType::UPDATE_FAILED, "���� ����!");
		CASE_LOG_BREAK(EErrorType::RENDER_FAILED, "������ ����!");
		CASE_LOG_BREAK(EErrorType::FINAL_FAILED, "������ ����!");

		CASE_LOG_BREAK(EErrorType::UNKNOWN_CONSOLE_SCREEN_BUFFER_TYPE, "�� �� ���� �ܼ� ��ũ�� ����!");
		CASE_LOG_BREAK(EErrorType::UNKNOWN_CONSOLE_COLOR, "�� �� ���� �ܼ� ����!");
		CASE_LOG_BREAK(EErrorType::UNKNOWN_CONSOLE_OUTPUT_TYPE, "�� �� ���� �ܼ� ��� Ÿ��!");
		CASE_LOG_BREAK(EErrorType::UNKNOWN_INTRO_MENU_SCENE_LOADER_TYPE, "�� �� ���� ��Ʈ�� �޴� �� �δ� Ÿ��!");
		CASE_LOG_BREAK(EErrorType::UNKNOWN_FRAME_RATE_TYPE, "�� �� ���� ������ ����Ʈ Ÿ��!");

		CASE_LOG_BREAK(EErrorType::NO_FRAME_LIMITED_ON_UNLIMITED_FRAME_RATE, "������ ������ ����Ʈ������ ������ ������ �� �� ����!");
		CASE_LOG_BREAK(EErrorType::INPUT_MAPPING_VAL_IS_ONLY_UPPERCASE, "�Է� ���� �Է°��� �빮�ڸ� ����!");
		CASE_LOG_BREAK(EErrorType::INPUT_MAPPING_SECOND_ARG_IS_NOT_AVAILABLE_STRING, "�Է� ���� �Է°��� �� ��° ���ڴ� ���ڿ��� �� �� ����!");
	}

	__debugbreak();
}

/*
���� Ÿ�Կ� �ش�Ǵ� ���ڿ��� �̸� ������ ���ڿ��� �����ݴϴ�.
*/
void ErrorHandler::ShowFormatString(const std::string_view& szError)
{
	DEBUG_LOG_CATEGORY(ErrorHandler, szError.data());
	__debugbreak();
}

/*
���� Ÿ�Կ� ���� ���� ���ڿ��� ��ȯ�մϴ�.
*/
std::string_view ErrorHandler::ToFormatString(EErrorType errorType)
{
	switch (errorType)
	{
		CASE_RETURN_STRING(EErrorType::NULLPTR, "(%s)�� ���������� ���¿��� ������!");
		CASE_RETURN_STRING(EErrorType::NO_INPUT_MAPPING_INFO, "�Է� ���� ��Ͽ� (%s)�� �ش�Ǵ� ������ ����!");
		CASE_RETURN_STRING(EErrorType::NO_PERFORMANCE_PROFILE_INFO, "�������� ��Ͽ� (%d)�� �ش�Ǵ� ������ ����!");
		CASE_RETURN_STRING(EErrorType::OVERLAPPED_SCENE, "(%s) ���� �̹� ��ϵǾ�����!");
	}

	return "��ϵ� ���� ���� ���ڿ��� ����!";
}
