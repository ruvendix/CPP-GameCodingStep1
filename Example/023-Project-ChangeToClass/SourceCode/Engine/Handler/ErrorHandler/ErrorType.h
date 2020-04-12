// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 에러 타입 모음입니다.
// 새로운 에러 타입은 여기에 추가해야 합니다.
// =====================================================================================

#ifndef ERROR_TYPE__H__
#define ERROR_TYPE__H__

#include "Common\CommonType.h"

enum class EErrorType : Int32
{
	NOTHING = 0,
	INIT_FAIL,
	INPUT_FAIL,
	UPDATE_FAIL,
	RENDER_FAIL,
	FINAL_FAIL,
	SAVE_FILE_FAIL,
	LOAD_FILE_FAIL,
	NULLPTR,
	UNKNOWN_CONSOLE_SCREEN_BUFFER_TYPE,
	UNKNOWN_CONSOLE_COLOR,
	UNKNOWN_CONSOLE_OUTPUT_TYPE,
	UNKNOWN_SCENE_TYPE,
	UNKNOWN_PHASE_TYPE,
	UNKNOWN_FRAME_RATE_TYPE,
	UNKNOWN_STATIC_OBJ,
	UNKNOWN_DYNAMIC_OBJ,
	NO_FRAME_LIMITED_ON_UNLIMITED_FRAME_RATE,
	NO_INPUT_MAPPING_INFO,
	NO_ITEM_IN_INVEN,
	INPUT_MAPPING_VALUE_IS_ONLY_UPPERCASE,
	INPUT_MAPPING_SECOND_ARG_IS_NOT_AVAILABLE_STRING,
	NO_PERFORMANCE_PROFILE_INFO,
	NO_PREV_CONSOLE_SELECTOR,
	NO_INPUT_FOCUS,
	NO_ROOT_PATH,
	NO_RESOURCE_PATH,
	OVERLAPPED_SCENE,
	FULL_INVEN,
	NOT_ENOUGH_GAME_MONEY,
	NOT_OPEN_FILE_STREAM,
	INVALID_RANGE,
	INVALID_MATRIX,
	FIRST_INPUT,
	FILE_STREAM_OPEN_FAIL,
};

#endif