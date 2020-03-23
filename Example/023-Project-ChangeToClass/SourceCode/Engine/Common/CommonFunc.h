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
#include "CommonType.h"
#include "CommonStruct.h"
#include "CommonMacro.h"

class CommonFunc final
{
    NON_COPYABLE_ONLY_PRIVATE_CLASS(CommonFunc);

public:
#pragma region 템플릿 함수

    /*
    열거형 클래스의 바탕 타입을 알려줍니다.
    */
    template <typename EType>
    static constexpr auto ToUnderlyingType(EType val) noexcept
    {
        static_assert(std::is_enum_v<EType>, "Only use enum type!");
        return static_cast<std::underlying_type_t<EType>>(val);
    }

    /*
    컨테이너의 요소에 중복된 값이 있는지 알려줍니다.
    */
    template <typename TContainer>
    static bool IsOverlapVal(const TContainer& container, const typename TContainer::value_type& val)
    {
        for (const auto& iter : container)
        {
            if (iter == val)
            {
                return true;
            }
        }

        return false;
    }
#pragma endregion

#pragma region 일반 함수
    static std::string MakeFormatString(const char* szFormat, ...);
    static bool InputNumClamp(_Out_ Int32& num, Int32 minNum, Int32 maxNum); // 직관적이도록 _Out_을 맨 앞으로!
#pragma endregion

#pragma region 매크로에서만 사용되는 함수
    static void ShowLog(const std::string_view& szLogCategory, const std::string_view& szLog);
#pragma endregion

};

#endif