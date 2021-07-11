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

#include "Common/CommonBase.h"
#include "Common/CommonType.h"

#include "MakeFormatString.hpp"

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

/*
	자식 클래스를 부모 클래스로 다운캐스팅합니다.
*/
template <typename TParent, typename TChild>
TChild* DownCast(TParent* pChild)
{
	static_assert(std::is_base_of_v<TParent, TChild>, "It's not parent!");
	return static_cast<TChild*>(pChild);
}

/*
	자식 클래스를 부모 클래스로 다운캐스팅합니다. (스마트 포인터)
*/
template <typename TParent, typename TChild>
std::shared_ptr<TChild> DownCastSmartPointer(std::shared_ptr<TParent> spChild)
{
	static_assert(std::is_base_of_v<TParent, TChild>, "It's not parent!");
	return std::static_pointer_cast<TChild>(spChild);
}

/*
	자식 클래스를 부모 클래스로 다운캐스팅합니다. (const 스마트 포인터)
*/
template <typename TParent, typename TChild>
const std::shared_ptr<TChild> ConstDownCastSmartPointer(const std::shared_ptr<TParent> spChild)
{
	static_assert(std::is_base_of_v<TParent, TChild>, "It's not parent!");
	return std::static_pointer_cast<TChild>(spChild);
}