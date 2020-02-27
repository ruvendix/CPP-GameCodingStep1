// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ConsoleController���� ���Ǵ� �������Դϴ�.
// =====================================================================================

#ifndef CONSOLE_CONTROLLER_ENUM__H__
#define CONSOLE_CONTROLLER_ENUM__H__

enum class EConsoleScreenBufferType : Int32
{
	FRONT = 0,
	BACK,
	MAX,
};

// ���ڻ��� ���� �� �� ���˴ϴ�.
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