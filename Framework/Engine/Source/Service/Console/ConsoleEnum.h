// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 콘솔 서비스에 사용되는 열거형입니다.
// =====================================================================================
#pragma once

#include "Common/CommonType.h"

// 각 색깔 명칭은 "https://docs.microsoft.com/ko-kr/windows-server/administration/windows-commands/color" 여기서 가져왔습니다.
// 글자뿐만 아니라 배경색에도 사용됩니다.
enum class EConsoleRenderingColor : Int32
{
	UNKNOWN = -1,
	BLACK,
	BLUE,
	GREEN,
	AQUA,
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_AQUA,
	LIGHT_RED,
	LIGHT_PURPLE,
	LIGHT_YELLOW,
	BRIGHT_WHITE,
};

enum class EConsoleRenderingType : Int32
{
	TEXT = 0,
	BACKGROUND,
};

enum class EConsoleOutputBufferType : Int32
{
	FRONT = 0,
	BACK,
	COUNT,
};