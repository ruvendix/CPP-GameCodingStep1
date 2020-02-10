// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#ifndef GLOBAL_FUNC__H__
#define GLOBAL_FUNC__H__

#include "GlobalMacro.h"

/*
    ���������� ���Ǵ� �Լ����� �����̿���!
    ��� �Լ��� static���� ���� �� �����ؾ� �մϴ�.
*/
class GlobalFunc
{
    NON_COPYABLE_CLASS(GlobalFunc);
    ONLY_PRIVATE_CLASS(GlobalFunc);

public:
#pragma region ���ø� �Լ� �����Դϴ�.
    template <typename EType>
    static constexpr auto ToUnderlyingType(EType val) noexcept
    {
        static_assert(std::is_enum_v<EType>, "Only use enum type!");
        return static_cast<std::underlying_type_t<EType>>(val);
    }
#pragma endregion

#pragma region �Ϲ� �Լ� �����Դϴ�.
    static void PauseGameApp();
    static void ClearConsoleScreen();
    static void ClearStdInputBuffer();
    static void MoveConsolePos(Int32 x, Int32 y);
    static COORD GetCurrentConsolePos();
    static bool InputNumClamp(_Out_ Int32& num, Int32 minNum, Int32 maxNum); // �������̵��� _Out_�� �� ������!
    static Int32 Clamp(Int32 val, Int32 minVal, Int32 maxVal);
    static EConsoleTextColorType QueryCurrentConsoleTextColor();
#pragma endregion

};

#endif