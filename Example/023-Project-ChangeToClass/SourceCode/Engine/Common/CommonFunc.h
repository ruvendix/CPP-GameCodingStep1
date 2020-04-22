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

#include "CommonNecessary.h"
#include "CommonStruct.h"
#include "CommonMacro.h"
#include "Handler\ErrorHandler\ErrorHandler.h"

using TimePoint = std::chrono::system_clock::time_point;

namespace common_func
{

#pragma region 일반 함수
    void DrawBorder(const COORD& pos, const SizeInfo& size);
    std::string MakeFormatString(const char* szFormat, ...);
    bool InputNumClamp(_Out_ Int32& num, Int32 minNum, Int32 maxNum); // 직관적이도록 _Out_을 맨 앞으로!
#pragma endregion

#pragma region 매크로에서만 사용되는 함수
    void ShowLog(const std::string_view& szLogCategory, const std::string_view& szLog);
#pragma endregion

} // namespace common_func end

#endif