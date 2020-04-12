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

#include "CommonStruct.h"
#include "CommonMacro.h"
#include "Handler\ErrorHandler\ErrorHandler.h"
#include "Core\FastRTTI.h"

class CommonFunc final
{
    NON_COPYABLE_ONLY_PRIVATE_CLASS(CommonFunc);

public:
#pragma region �Ϲ� �Լ�
    static std::string MakeFormatString(const char* szFormat, ...);
    static bool InputNumClamp(_Out_ Int32& num, Int32 minNum, Int32 maxNum); // �������̵��� _Out_�� �� ������!
#pragma endregion

#pragma region ��ũ�ο����� ���Ǵ� �Լ�
    static void ShowLog(const std::string_view& szLogCategory, const std::string_view& szLog);
#pragma endregion

#pragma region ���ø� �Լ�
    /*
    ������ Ŭ������ ���� Ÿ���� �˷��ݴϴ�.
    */
    template <typename EType>
    static constexpr auto ToUnderlyingType(EType value) noexcept
    {
        static_assert(std::is_enum_v<EType>, "Only use enum type!");
        return static_cast<std::underlying_type_t<EType>>(value);
    }

    /*
    �����̳��� ��ҿ� �ߺ��� ���� �ִ��� �˷��ݴϴ�.
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
    ���� Ŭ������ ���� Ŭ���� �迭���� �˷��ݴϴ�.
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
    �� Ŭ������ Ÿ���� ������ �˷��ݴϴ�. (RTTI ���� �ʼ�!)
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
    ���� Ŭ������ �����Ϳ� �ִ� ���� ��ü�� ���� Ŭ������ �����ͷ� ĳ�������ݴϴ�.
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