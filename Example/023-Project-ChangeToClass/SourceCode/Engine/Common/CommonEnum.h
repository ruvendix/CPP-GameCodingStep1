// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 공용으로 사용되는 열거형 모음입니다.
// C26812에 의해 열거형 클래스만 사용합니다.
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

// 입력값 하나에 대한 상태가 아니라 입력 조합에 대한 상태에요!
enum class EInputMappingState : Int32
{
	NONE = 0, // 입력 조합을 누르지 않은 상태
	UP,       // 입력 조합을 뗀 상태
	PRESSING, // 입력 조합을 누르고 있는 상태
	DOWN,     // 입력 조합을 누른 상태
	MAX,
};

#endif