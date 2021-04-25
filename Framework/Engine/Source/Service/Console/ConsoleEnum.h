// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ܼ� ���񽺿� ���Ǵ� �������Դϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonType.h"

// �� ���� ��Ī�� "https://docs.microsoft.com/ko-kr/windows-server/administration/windows-commands/color" ���⼭ �����Խ��ϴ�.
// ���ڻӸ� �ƴ϶� �������� ���˴ϴ�.
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