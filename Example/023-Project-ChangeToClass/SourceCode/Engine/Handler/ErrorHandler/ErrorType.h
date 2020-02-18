// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 오류 종류 모음입니다.
// 새로운 오류는 여기에 추가해야 합니다.
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
};

#endif