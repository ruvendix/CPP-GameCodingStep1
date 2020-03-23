// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �������� ���Ǵ� ���ø� �����Դϴ�.
// ���ø� �Լ��� CommonFunc�� �з��ϰ�, TMP(Template Meta Programming)�� ���⿡ �ش�˴ϴ�.
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