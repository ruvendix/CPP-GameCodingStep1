// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 에러 핸들러에 사용되는 열거형입니다.
// =====================================================================================
#pragma once

#include "Common/CommonType.h"

enum class EErrorType : Int32
{
	UNKNOWN = -1,
	INDIRECT_NULLPTR, // 널포인터 역참조
	OUT_OF_GAMEOBJECT, // 게임 오브젝트 매니저가 수용 가능한 개수 초과
	COUNT,
};