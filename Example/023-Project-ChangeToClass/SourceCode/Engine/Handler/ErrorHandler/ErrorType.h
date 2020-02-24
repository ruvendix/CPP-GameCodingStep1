// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� Ÿ�� �����Դϴ�.
// ���ο� ���� Ÿ���� ���⿡ �߰��ؾ� �մϴ�.
// =====================================================================================

#ifndef ERROR_TYPE__H__
#define ERROR_TYPE__H__

#include "Common\CommonType.h"

enum class EErrorType : Int32
{
	NONE = 0,
	INIT_FAILED,
	UPDATE_FAILED,
	RENDER_FAILED,
	FINAL_FAILED,
	NULLPTR,
	UNKNOWN_CONSOLE_SCREEN_BUFFER_TYPE,
	UNKNOWN_CONSOLE_COLOR,
	UNKNOWN_CONSOLE_OUTPUT_TYPE,
	NO_FRAME_LIMITED_ON_UNLIMITED_FRAME_RATE,
	NO_INPUT_MAPPING_INFO,
	INPUT_MAPPING_VAL_IS_ONLY_UPPERCASE,
	INPUT_MAPPING_SECOND_ARG_IS_NOT_AVAILABLE_STRING,
	NO_PERFORMANCE_PROFILE_INFO,
	OVERLAPPED_SCENE,
};

#endif