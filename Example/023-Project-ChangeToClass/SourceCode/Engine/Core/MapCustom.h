// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �� �� ���ϰ� ����� �� �ֽ��ϴ�.
// ���� ���, �ݹ��� �ʿ� ����� �� ���� ��� �����մϴ�.
// Ű���� �̿��ϹǷ� ��� ������ ������� ����� �� �ֽ��ϴ�.
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

#pragma region ������ �� �Ҹ���
	MapCustom() = default;
	~MapCustom() = default;
#pragma endregion

	void Subscribe(TKey key, TElem elem)
	{
		auto ret = m_map.insert(std::make_pair(key, elem));

		// �ʿ� ���������� ��ϵǾ����� �߰� Ȯ��!
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