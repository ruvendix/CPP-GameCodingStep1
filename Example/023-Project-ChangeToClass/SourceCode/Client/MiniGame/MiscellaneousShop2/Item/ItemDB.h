// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 아이템 묶음입니다. 이런 걸 데이터베이스, DB라고 하죠.
// 하나에 모아도 되지만 일반적으로 DB는 여러 개로 분리되어있어요.
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

#pragma region 생성자 및 소멸자
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
		
		// 맵에 공간을 확보한 후에 동적할당
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