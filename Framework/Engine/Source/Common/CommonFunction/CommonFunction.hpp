// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���������� ���Ǵ� �Լ� �����Դϴ�.
// �Ϲ� �Լ��� ���ø� �Լ��� ���Ե˴ϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "Common/CommonType.h"

#include "MakeFormatString.hpp"

/*
	printf()�� ���� ���ø� �����Դϴ�.
*/
template <typename... Args>
void PrintF(Char const* szFormat, Args&&... args)
{
    printf(szFormat, std::forward<Args>(args)...);
}

/*
	������ Ŭ������ ��� �ڷ����� �˷��ݴϴ�.
*/
template <typename EType>
static constexpr auto ToUnderlyingType(EType value)
{
	static_assert(std::is_enum_v<EType>, "Only use enum type!");
	return static_cast<std::underlying_type_t<EType>>(value);
}

/*
	�ڽ� Ŭ������ �θ� Ŭ������ �ٿ�ĳ�����մϴ�.
*/
template <typename TParent, typename TChild>
TChild* DownCast(TParent* pChild)
{
	static_assert(std::is_base_of_v<TParent, TChild>, "It's not parent!");
	return static_cast<TChild*>(pChild);
}

/*
	�ڽ� Ŭ������ �θ� Ŭ������ �ٿ�ĳ�����մϴ�. (����Ʈ ������)
*/
template <typename TParent, typename TChild>
std::shared_ptr<TChild> DownCastSmartPointer(std::shared_ptr<TParent> spChild)
{
	static_assert(std::is_base_of_v<TParent, TChild>, "It's not parent!");
	return std::static_pointer_cast<TChild>(spChild);
}

/*
	�ڽ� Ŭ������ �θ� Ŭ������ �ٿ�ĳ�����մϴ�. (const ����Ʈ ������)
*/
template <typename TParent, typename TChild>
const std::shared_ptr<TChild> ConstDownCastSmartPointer(const std::shared_ptr<TParent> spChild)
{
	static_assert(std::is_base_of_v<TParent, TChild>, "It's not parent!");
	return std::static_pointer_cast<TChild>(spChild);
}