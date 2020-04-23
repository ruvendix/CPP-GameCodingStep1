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

#include "Controller\ConsoleController.h"

DEFINE_LOG_CATEGORY(ErrorHandler);

COORD ErrorHandler::m_renderPos;
std::string ErrorHandler::m_strError;

/*
���� Ÿ�Կ� �ش�Ǵ� ���ڿ��� ��ȯ�մϴ�.
*/
std::string_view ErrorHandler::ToString(EErrorType errorType)
{
	switch (errorType)
	{
		CASE_RETURN_STRING(EErrorType::INIT_FAIL, "�ʱ�ȭ ����!");
		CASE_RETURN_STRING(EErrorType::INPUT_FAIL, "�Է� ó�� ����!");
		CASE_RETURN_STRING(EErrorType::UPDATE_FAIL, "���� ����!");
		CASE_RETURN_STRING(EErrorType::RENDER_FAIL, "������ ����!");
		CASE_RETURN_STRING(EErrorType::FINAL_FAIL, "������ ����!");
		CASE_RETURN_STRING(EErrorType::COPY_FAIL, "���� ����!");	
		CASE_RETURN_STRING(EErrorType::INSERT_FAIL, "���� ����!");		

		CASE_RETURN_STRING(EErrorType::UNKNOWN_CONSOLE_SCREEN_BUFFER_TYPE, "�� �� ���� �ܼ� ��ũ�� ����!");
		CASE_RETURN_STRING(EErrorType::UNKNOWN_CONSOLE_COLOR, "�� �� ���� �ܼ� ����!");
		CASE_RETURN_STRING(EErrorType::UNKNOWN_CONSOLE_OUTPUT_TYPE, "�� �� ���� �ܼ� ��� Ÿ��!");
		CASE_RETURN_STRING(EErrorType::UNKNOWN_SCENE_TYPE, "�� �� ���� �� Ÿ��!");
		CASE_RETURN_STRING(EErrorType::UNKNOWN_PHASE_TYPE, "�� �� ���� ������ Ÿ��!");
		CASE_RETURN_STRING(EErrorType::UNKNOWN_FRAME_RATE_TYPE, "�� �� ���� ������ ����Ʈ Ÿ��!");
		CASE_RETURN_STRING(EErrorType::UNKNOWN_STATIC_OBJ, "�� �� ���� ���� ������Ʈ Ÿ��!");		
		CASE_RETURN_STRING(EErrorType::UNKNOWN_DYNAMIC_OBJ, "�� �� ���� ���� ������Ʈ Ÿ��!");
		CASE_RETURN_STRING(EErrorType::UNKNOWN_ELEM, "�� �� ���� ���!");

		CASE_RETURN_STRING(EErrorType::NO_FRAME_LIMITED_ON_UNLIMITED_FRAME_RATE, "������ ������ ����Ʈ������ ������ ������ �� �� ����!");
		CASE_RETURN_STRING(EErrorType::NO_PREV_CONSOLE_SELECTOR, "���� �ܼ� �����Ͱ� ����!");
		CASE_RETURN_STRING(EErrorType::NO_ITEM_IN_INVEN, "�κ��� �������� ����!");
		CASE_RETURN_STRING(EErrorType::NO_INPUT_FOCUS, "�Է� ��Ŀ���� ����!");
		CASE_RETURN_STRING(EErrorType::NO_ROOT_PATH, "��Ʈ ��ΰ� ����!");
		
		CASE_RETURN_STRING(EErrorType::INPUT_MAPPING_VALUE_IS_ONLY_UPPERCASE, "�Է� ���� �Է°��� �빮�ڸ� ����!");
		CASE_RETURN_STRING(EErrorType::INPUT_MAPPING_SECOND_ARG_IS_NOT_AVAILABLE_STRING, "�Է� ���� �Է°��� �� ��° ���ڴ� ���ڿ��� �� �� ����!");
		CASE_RETURN_STRING(EErrorType::FULL_INVEN, "�κ��� ���� á��!");

	default:
	{
		return ToFormatString(errorType);
	}
	}

	return "��ϵ� ���� ���ڿ��� ����!";
}

/*
���� Ÿ�Կ� �ش�Ǵ� �̸� ������ ���ڿ��� �������մϴ�.
*/
void ErrorHandler::RenderString()
{
	PUT_STRING(m_renderPos.X, m_renderPos.Y, m_strError.c_str());
}

/*
���� Ÿ�Կ� �ش�Ǵ� �̸� ������ ���ڿ��� ����� ���â�� �����ݴϴ�.
*/
void ErrorHandler::OuputDebugString(bool bOutput)
{
	if (bOutput == true)
	{
		DEBUG_LOG_CATEGORY(ErrorHandler, m_strError.data());
	}
}

/*
����� ����� ���� �ش� ��ġ���� �ߴ��մϴ�.
*/
void ErrorHandler::DebugBreak(bool bDebugBreak)
{
	if (bDebugBreak == true)
	{
		__debugbreak();
	}
}

/*
���� Ÿ�Կ� �ش�Ǵ� ���� ���ڿ��� ��ȯ�մϴ�.
*/
std::string_view ErrorHandler::ToFormatString(EErrorType errorType)
{
	switch (errorType)
	{
		CASE_RETURN_STRING(EErrorType::NULLPTR, "(%s)�� ���������� ���¿��� ������!");
		CASE_RETURN_STRING(EErrorType::NO_INPUT_MAPPING_INFO, "�Է� ���� ��Ͽ� (%s)�� �ش�Ǵ� ������ ����!");
		CASE_RETURN_STRING(EErrorType::NO_PERFORMANCE_PROFILE_INFO, "�������� ��Ͽ� (%d)�� �ش�Ǵ� ������ ����!");
		CASE_RETURN_STRING(EErrorType::NO_RESOURCE_PATH, "(%s)�� �ùٸ� ���ҽ� ��ΰ� �ƴ�!");
		CASE_RETURN_STRING(EErrorType::OVERLAPPED_SCENE, "(%s) ���� �̹� ��ϵǾ�����!");
		CASE_RETURN_STRING(EErrorType::NOT_ENOUGH_GAME_MONEY, "���� �� (%d)������ ������ ���� (%d)���� �� ����!");
		CASE_RETURN_STRING(EErrorType::NOT_OPEN_FILE_STREAM, "(%s)�� ���� ��Ʈ���� ���µ��� �ʾ���!");
		CASE_RETURN_STRING(EErrorType::INVALID_RANGE, "���簪(%d)�� �ּڰ�(%d) ~ �ִ�(%d)�� ������ ���!");
		CASE_RETURN_STRING(EErrorType::INVALID_MATRIX, "���簪(%d, %d)�� �ּڰ�(%d, %d) ~ �ִ�(%d, %d)�� ������ ���!");
		CASE_RETURN_STRING(EErrorType::FILE_STREAM_OPEN_FAIL, "(%s)�� ���� ��Ʈ�� ���� ����!");		
		CASE_RETURN_STRING(EErrorType::SAVE_FILE_FAIL, "(%s) ���� ����!");
		CASE_RETURN_STRING(EErrorType::LOAD_FILE_FAIL, "(%s) �ҷ����� ����!");		
	}

	return "��ϵ� ���� ���� ���ڿ��� ����!";
}
