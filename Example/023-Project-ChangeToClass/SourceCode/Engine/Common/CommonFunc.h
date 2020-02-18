// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 공용으로 사용되는 함수 선언 모음입니다.
// 모든 함수는 static으로 선언 및 정의해야 합니다.
// =====================================================================================

#ifndef COMMON_FUNC__H__
#define COMMON_FUNC__H__

#include "Common\CommonMacro.h"

class CommonFunc final
{
    NON_COPYABLE_ONLY_PRIVATE_CLASS(CommonFunc);

public:
#pragma region 템플릿 함수 모음입니다.
    template <typename EType>
    static constexpr auto ToUnderlyingType(EType val) noexcept
    {
        static_assert(std::is_enum_v<EType>, "Only use enum type!");
        return static_cast<std::underlying_type_t<EType>>(val);
    }
#pragma endregion

#pragma region 일반 함수 모음입니다.
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
    static bool InputNumClamp(_Out_ Int32& num, Int32 minNum, Int32 maxNum); // 직관적이도록 _Out_을 맨 앞으로!
    static Int32 Clamp(Int32 val, Int32 minVal, Int32 maxVal);
    static Int32 ClampCircular(Int32 val, Int32 minVal, Int32 maxVal);
    static EConsoleTextColorType QueryCurrentConsoleTextColor();
#pragma endregion

#pragma region 매크로에서만 사용되는 함수 모음입니다.
    static void ShowLog(const std::string_view& szLogCategory, const std::string_view& szLog);
#pragma endregion

};

#endif