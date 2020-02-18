// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �������� ���Ǵ� ������ �����Դϴ�.
// C26812�� ���� ������ Ŭ������ ����մϴ�.
// =====================================================================================

#ifndef COMMON_ENUM__H__
#define COMMON_ENUM__H__

#include "Common\CommonType.h"

enum class EGameState : Int32
{
	NONE = 0,
	INIT,
	UPDATE,
	RENDER,
	FINAL,
	TERMINATION_SUCCESS,
	TERMINATION_ABNORMALITY,
};

enum class ESceneType : Int32
{
	CURRENT = 0,
	NEXT,
};

enum class EConsoleTextColorType : Int32
{
	BLACK = 0,
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

// �Է°� �ϳ��� ���� ���°� �ƴ϶� �Է� ���տ� ���� ���¿���!
enum class EInputMappingState : Int32
{
	NONE = 0, // �Է� ������ ������ ���� ����
	UP,       // �Է� ������ �� ����
	PRESSING, // �Է� ������ ������ �ִ� ����
	DOWN,     // �Է� ������ ���� ����
	MAX,
};

#endif