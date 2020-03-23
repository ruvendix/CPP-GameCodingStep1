// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 공용으로 사용되는 템플릿 모음입니다.
// 템플릿 함수는 CommonFunc로 분류하고, TMP(Template Meta Programming)가 여기에 해당됩니다.
// =====================================================================================

#ifndef COMMON_TEMPLATE__H__
#define COMMON_TEMPLATE__H__

template <typename TPair>
struct TSecond
{
    typename TPair::second_type operator()(const TPair& pair) const
    { 
        return pair.second;
    }
};

template <typename TMap>
TSecond<typename TMap::value_type> GetSecond(const TMap& map)
{ 
    return TSecond<typename TMap::value_type>();
}

#endif