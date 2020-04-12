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

#include "CommonStruct.h"
#include "CommonMacro.h"
#include "Handler\ErrorHandler\ErrorHandler.h"
#include "Core\FastRTTI.h"

class CommonFunc final
{
    NON_COPYABLE_ONLY_PRIVATE_CLASS(CommonFunc);

public:
#pragma region 일반 함수
    static std::string MakeFormatString(const char* szFormat, ...);
    static bool InputNumClamp(_Out_ Int32& num, Int32 minNum, Int32 maxNum); // 직관적이도록 _Out_을 맨 앞으로!
#pragma endregion

#pragma region 매크로에서만 사용되는 함수
    static void ShowLog(const std::string_view& szLogCategory, const std::string_view& szLog);
#pragma endregion

#pragma region 템플릿 함수
    /*
    열거형 클래스의 바탕 타입을 알려줍니다.
    */
    template <typename EType>
    static constexpr auto ToUnderlyingType(EType value) noexcept
    {
        static_assert(std::is_enum_v<EType>, "Only use enum type!");
        return static_cast<std::underlying_type_t<EType>>(value);
    }

    /*
    컨테이너의 요소에 중복된 값이 있는지 알려줍니다.
    */
    template <typename TContainer>
    static bool IsOverlapValue(const TContainer& container, const typename TContainer::value_type& value)
    {
        for (const auto& iter : container)
        {
            if (iter == value)
            {
                return true;
            }
        }

        return false;
    }

    /*
    하위 클래스가 상위 클래스 계열인지 알려줍니다.
    */
    template <typename TParent>
    bool IsKindOf(const TParent* pChild)
    {
        CHECK_NULLPTR_RETURN(pChild, false);
        const char* szParentClassName = TParent::GetRTTI()->getClassName();

        const FastRTTI* pRTTI = pChild->OnGetRTTI();
        while (pRTTI != nullptr)
        {
            if (pRTTI->getClassName() == szParentClassName)
            {
                return true;
            }

            pRTTI = pRTTI->getParent();
        }

        return false;
    }

    /*
    두 클래스의 타입이 같은지 알려줍니다. (RTTI 정보 필수!)
    */
    template <typename TDestRTTI, typename TSrcRTTI>
    bool IsSameOf(const TSrcRTTI* pSrcRTTI)
    {
        CHECK_NULLPTR_RETURN(pSrcRTTI, false);
        if (pSrcRTTI->OnGetRTTI()->getClassName() == std::remove_pointer_t<TDestRTTI>::GetRTTI()->getClassName())
        {
            return true;
        }

        return false;
    }

    /*
    상위 클래스의 포인터에 있는 동적 객체를 하위 클래스의 포인터로 캐스팅해줍니다.
    */
    template <typename TChild, typename TParent>
    TChild KindCast(const TParent* pChild)
    {
        using TChildPrototype = std::remove_pointer_t<TChild>;

        if (IsSameOf<TChildPrototype*>(pChild))
        {
            return (TChildPrototype*)(pChild);
        }

        return nullptr;
    }
#pragma endregion

};

#endif