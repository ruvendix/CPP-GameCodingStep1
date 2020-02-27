// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// ConsoleController에서 사용되는 열거형입니다.
// =====================================================================================

#ifndef CONSOLE_CONTROLLER_ENUM__H__
#define CONSOLE_CONTROLLER_ENUM__H__

enum class EConsoleScreenBufferType : Int32
{
	FRONT = 0,
	BACK,
	MAX,
};

// 글자색과 배경색 둘 다 사용됩니다.
enum class EConsoleOutputColorType : Int32
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

enum class EConsoleOutputType : Int32
{
	TEXT = 0,
	BACKGROUND,
};

#endif