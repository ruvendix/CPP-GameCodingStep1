// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 공통적으로 사용되는 함수 모음입니다.
// 일반 함수와 템플릿 함수가 포함됩니다.
// =====================================================================================
#pragma once

#include "CommonBase.h"
#include "CommonType.h"

#include "CommonFunction/MakeFormatString.hpp"

/*
	printf()의 가변 템플릿 버전입니다.
*/
template <typename... Args>
void PrintF(Char const* szFormat, Args&&... args)
{
    printf(szFormat, std::forward<Args>(args)...);
}

/*
	열거형 클래스의 기반 자료형을 알려줍니다.
*/
template <typename EType>
static constexpr auto ToUnderlyingType(EType value)
{
	static_assert(std::is_enum_v<EType>, "Only use enum type!");
	return static_cast<std::underlying_type_t<EType>>(value);
}