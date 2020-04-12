// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 공용으로 사용되는 템플릿 모음입니다.
// 템플릿 구조체, 템플릿 클래스, 템플릿 함수가 포함됩니다.
// =====================================================================================

#ifndef COMMON_TEMPLATE__H__
#define COMMON_TEMPLATE__H__

namespace common_func
{

    /*
    map에서 비교할 때 사용되는 보조 구조체입니다.
    */
    template <typename TPair>
    struct TSecond
    {
        typename TPair::second_type operator()(const TPair& pair) const
        {
            return pair.second;
        }
    };

    /*
    map에서 비교하기 위해 second를 가져옵니다.
    */
    template <typename TMap>
    TSecond<typename TMap::value_type> GetSecond(const TMap& map)
    {
        return TSecond<typename TMap::value_type>();
    }

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
    template <typename TChildPtr, typename TParent>
    bool IsKindOf(const TParent* pChild)
    {
        CHECK_NULLPTR_RETURN(pChild, false);
        const char* szTargetClassName = std::remove_pointer_t<TChildPtr>::GetRTTI()->getClassName();

        const FastRTTI* pRTTI = pChild->OnGetRTTI();
        while (pRTTI != nullptr)
        {
            if (pRTTI->getClassName() == szTargetClassName)
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
    template <typename TSrc, typename TDestPtr>
    bool IsSameOf(const TSrc* pSrcRTTI)
    {
        CHECK_NULLPTR_RETURN(pSrcRTTI, false);
        if (pSrcRTTI->OnGetRTTI()->getClassName() == std::remove_pointer_t<TDestPtr>::GetRTTI()->getClassName())
        {
            return true;
        }

        return false;
    }

    /*
    상위 클래스의 포인터에 있는 동적 객체를 하위 클래스의 포인터로 캐스팅해줍니다.
    */
    template <typename TChildPtr, typename TParent>
    TChildPtr KindCast(const TParent* pChild)
    {
        if (IsKindOf<TChildPtr>(pChild))
        {
            return (TChildPtr)(pChild);
        }

        return nullptr;
    }
    
    /*
    shared_ptr의 실제 동적 객체를 shared_ptr로 반환합니다.
    */
    template <typename TChild, class TParent>
    std::shared_ptr<TChild> KindCastSP(const std::shared_ptr<TParent>& spChild)
    {
        using TChildPtr = typename std::shared_ptr<TChild>::element_type*;
        const auto ptr = KindCast<TChildPtr>(&*spChild);

        if (ptr != nullptr)
        {
            return std::shared_ptr<TChild>(spChild, ptr);
        }

        return nullptr;
    }

    /*
    shared_ptr의 실제 동적 객체를 shared_ptr로 반환합니다.
    */
    template <typename TChild, class TParent>
    std::shared_ptr<TChild> KindCastSP(std::shared_ptr<TParent>&& spChild)
    {
        using TChildPtr = typename std::shared_ptr<TChild>::element_type*;
        const auto ptr = KindCast<TChildPtr>(&*spChild);

        if (ptr != nullptr)
        {
            return std::shared_ptr<TChild>(std::move(spChild), ptr);
        }

        return nullptr;
    }

    template <typename TSrcContainer, typename TDestContainer>
    void CopySharedPtrContainer(const TSrcContainer& src, TDestContainer& dest)
    {
        using TSharedPtr = typename TDestContainer::value_type;
        using TElem = typename TSharedPtr::element_type;

        for (const auto& iter : src)
        {
            TSharedPtr spDest = common_func::KindCastSP<TElem>(iter);
            if (spDest != nullptr)
            {
                dest.push_back(spDest);
            }
        }
    }

} // namespace common_func end
#endif