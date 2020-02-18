// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �������� ���Ǵ� �Լ� ���� �����Դϴ�.
// ��� �Լ��� static���� ���� �� �����ؾ� �մϴ�.
// =====================================================================================

#ifndef COMMON_FUNC__H__
#define COMMON_FUNC__H__

#include "Common\CommonMacro.h"

class CommonFunc final
{
    NON_COPYABLE_ONLY_PRIVATE_CLASS(CommonFunc);

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
    static void AdjustConsoleArea(Int32 width, Int32 height);
    static void AdjustConsoleArea(const SizeInfo& sizeInfo);
    static void GameConsoleStyle();
    static void PauseGameApp();
    static void ClearConsoleScreen();
    static void ClearStdInputBuffer();
    static void MoveConsolePos(Int32 x, Int32 y);
    static void MoveConsolePos(const COORD& pos);
    static void AlignCenterToConsole(const SizeInfo& sizeInfo, Uint32 length);
    static void ChangeTitle(const std::string_view& szTitle);

    static std::string MakeFormatString(const char* szFormat, ...);
    static COORD GetCurrentConsolePos();
    static bool InputNumClamp(_Out_ Int32& num, Int32 minNum, Int32 maxNum); // �������̵��� _Out_�� �� ������!
    static Int32 Clamp(Int32 val, Int32 minVal, Int32 maxVal);
    static Int32 ClampCircular(Int32 val, Int32 minVal, Int32 maxVal);
    static EConsoleTextColorType QueryCurrentConsoleTextColor();
#pragma endregion

#pragma region ��ũ�ο����� ���Ǵ� �Լ� �����Դϴ�.
    static void ShowLog(const std::string_view& szLogCategory, const std::string_view& szLog);
#pragma endregion

};

#endif