// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �������� ���Ǵ� ���ø� �����Դϴ�.
// ���ø� ����ü, ���ø� Ŭ����, ���ø� �Լ��� ���Ե˴ϴ�.
// =====================================================================================

#ifndef COMMON_TEMPLATE__H__
#define COMMON_TEMPLATE__H__

namespace common_func
{

    /*
    map���� ���� �� ���Ǵ� ���� ����ü�Դϴ�.
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
    map���� ���ϱ� ���� second�� �����ɴϴ�.
    */
    template <typename TMap>
    TSecond<typename TMap::value_type> GetSecond(const TMap& map)
    {
        return TSecond<typename TMap::value_type>();
    }

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
    �� Ŭ������ Ÿ���� ������ �˷��ݴϴ�. (RTTI ���� �ʼ�!)
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
    ���� Ŭ������ �����Ϳ� �ִ� ���� ��ü�� ���� Ŭ������ �����ͷ� ĳ�������ݴϴ�.
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
    shared_ptr�� ���� ���� ��ü�� shared_ptr�� ��ȯ�մϴ�.
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
    shared_ptr�� ���� ���� ��ü�� shared_ptr�� ��ȯ�մϴ�.
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