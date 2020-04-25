// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 맵을 좀 더 편하게 사용할 수 있습니다.
// 예를 들면, 콜백을 맵에 등록할 때 쉽게 사용 가능합니다.
// 키값을 이용하므로 등록 순서에 관계없이 사용할 수 있습니다.
// =====================================================================================

#ifndef MAP_CUSTOM__H__
#define MAP_CUSTOM__H__

#include "Common\CommonNecessary.h"
#include "Common\CommonFunc.h"
#include "Handler\ErrorHandler\ErrorHandler.h"

template <typename TKey, typename TElem>
class MapCustom
{
public:
	using MapType = std::unordered_map<TKey, TElem>;
	using ElemType = TElem;

#pragma region 생성자 및 소멸자
	MapCustom() = default;
	~MapCustom() = default;
#pragma endregion

	void Subscribe(TKey key, TElem elem)
	{
		auto ret = m_map.insert(std::make_pair(key, elem));

		// 맵에 성공적으로 등록되었는지 추가 확인!
		if (ret.second == false)
		{
			//DEFAULT_ERROR_HANDLER(EErrorType::INSERT_FAIL);
		}
	}

	void Unsubscribe(TKey key)
	{
		auto& iter = m_map.find(key);
		m_map.erase(iter);
	}

	void Clear()
	{
		m_map.clear();
	}

	TElem Find(TKey key) const
	{
		const auto& iter = m_map.find(key);
		if (iter != m_map.cend())
		{
			return iter->second;
		}

		//ERROR_HANDLER(false, EErrorType::UNKNOWN_ELEM);
		return nullptr;
	}

	TSize Size() const
	{
		return m_map.size();
	}

	const MapType& getMap() const
	{
		return m_map;
	}

private:
	MapType m_map;
};

#endif