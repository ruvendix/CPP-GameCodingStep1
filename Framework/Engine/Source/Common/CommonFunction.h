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

#include "CommonBase.h"
#include "CommonType.h"

#include "CommonFunction/MakeFormatString.hpp"

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