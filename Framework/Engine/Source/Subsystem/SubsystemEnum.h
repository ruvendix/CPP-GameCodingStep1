// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 서브시스템에 사용되는 열거형입니다.
// =====================================================================================
#pragma once

#include "Common/CommonType.h"

enum class ESubsystemType : Int32
{
	UNKNOWN = -1,
	LOGGER,
	ERROR_HANLDER,
	CONSOLE_HANDLER,
	GAME_OBJECT_MANAGER,
	FRAME_TIME_MANAGER,
	TIME_HANDLER,
	PATH_MANAGER,
	FILE_HANDLER,
	COUNT,
};