// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// MakeFormatString()을 구현합니다.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "Common/CommonType.h"

/*
    std::string을 서식문자열과 호환시키려면 필요합니다.
*/
template <typename T>
T Argument(T value)
{
    return value;
}

/*
    std::string을 서식문자열과 호환되게 해줍니다.
    템플릿 오버로딩을 이용하려면 std::basic_string<T>을 이용해야 해요.
*/
template <typename T>
const char* Argument(const std::basic_string<T>& str)
{
    return str.c_str();
}

/*
    Char 배열에 서식문자열을 씁니다.
*/
template <typename... Args>
Int32 StringPrint(Char buffer[], size_t bufferCount, const Char* szFormat, Args&&... args)
{
    return snprintf(buffer, bufferCount, szFormat, Argument(std::forward<Args>(args))...);
}

/*
    서식문자열을 std::string으로 만듭니다.
*/
template <typename... Args>
std::string MakeFormatString(const Char* szFormat, Args&&... args)
{
    Int32 stringLength = StringPrint(nullptr, 0, szFormat, std::forward<Args>(args)...);

    std::string str;
    str.resize(stringLength);

    // snprintf()는 종료문자가 포함되었다고 가정하므로 +1을 해줘야 합니다.
    stringLength = StringPrint(str.data(), str.size() + 1, szFormat, std::forward<Args>(args)...);

    // 출력해야 할 문자열이 아직 남았을 경우(종료문자 제외)
    if (stringLength > static_cast<Int32>(str.size()))
    {
        str.resize(stringLength);
        StringPrint(str.data(), str.size() + 1, szFormat, std::forward<Args>(args)...);
    }
    // 출력해야 할 문자열 길이보다 남을 경우(종료문자 제외)
    else if (stringLength < static_cast<Int32>(str.size()))
    {
        str.resize(stringLength);
    }

    return str;
}