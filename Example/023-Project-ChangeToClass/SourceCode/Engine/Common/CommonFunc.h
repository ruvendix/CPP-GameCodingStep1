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

#include "CommonNecessary.h"
#include "CommonType.h"
#include "CommonStruct.h"
#include "CommonMacro.h"

class CommonFunc final
{
    NON_COPYABLE_ONLY_PRIVATE_CLASS(CommonFunc);

public:
#pragma region ���ø� �Լ�

    /*
    ������ Ŭ������ ���� Ÿ���� �˷��ݴϴ�.
    */
    template <typename EType>
    static constexpr auto ToUnderlyingType(EType val) noexcept
    {
        static_assert(std::is_enum_v<EType>, "Only use enum type!");
        return static_cast<std::underlying_type_t<EType>>(val);
    }

    /*
    �����̳��� ��ҿ� �ߺ��� ���� �ִ��� �˷��ݴϴ�.
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

#pragma region �Ϲ� �Լ�
    static std::string MakeFormatString(const char* szFormat, ...);
    static bool InputNumClamp(_Out_ Int32& num, Int32 minNum, Int32 maxNum); // �������̵��� _Out_�� �� ������!
#pragma endregion

#pragma region ��ũ�ο����� ���Ǵ� �Լ�
    static void ShowLog(const std::string_view& szLogCategory, const std::string_view& szLog);
#pragma endregion

};

#endif