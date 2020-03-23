// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������ �����Դϴ�. �̷� �� �����ͺ��̽�, DB��� ����.
// �ϳ��� ��Ƶ� ������ �Ϲ������� DB�� ���� ���� �и��Ǿ��־��.
// =====================================================================================

#ifndef ITEM_DB_H__
#define ITEM_DB_H__

#include "Common\CommonType.h"
#include "Common\CommonMacro.h"
#include "Common\CommonNecessary.h"

class ItemBase;

class ItemDB final
{
public:
	using MapItemDB = std::unordered_map<std::string, ItemBase*>;

#pragma region ������ �� �Ҹ���
	ItemDB() = default;
	~ItemDB();
#pragma endregion

	ItemBase* FindItem(const std::string& strNameTag) const;
	void CopyToVector(_Out_ std::vector<ItemBase*>& vecItem) const;

	const MapItemDB& getMapItemDB() const
	{
		return m_mapItem;
	}

	template <typename TItem>
	void InsertItem(const std::string_view& strNameTag, Int32 ID, Int32 price)
	{
		TItem* pItem = trace_new TItem;
		pItem->setNameTag(strNameTag);
		pItem->setID(ID);
		pItem->setPrice(price);
		
		// �ʿ� ������ Ȯ���� �Ŀ� �����Ҵ�
		auto ret = m_mapItem.insert(std::make_pair(strNameTag, nullptr));
		if (ret.second == true)
		{
			ret.first->second = pItem;
		}
 	}

private:
	MapItemDB m_mapItem;
};

#endif