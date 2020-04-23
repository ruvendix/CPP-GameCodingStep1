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

using ItemBasePtr = std::shared_ptr<ItemBase>;
using MapItemDB = MapCustom<std::string, ItemBasePtr>;

class ItemDB final
{
public:
#pragma region ������ �� �Ҹ���
	ItemDB() = default;
	~ItemDB() = default;
#pragma endregion

	ItemBasePtr FindItem(const std::string& strNameTag) const;
	void CopyToVector(_Out_ std::vector<ItemBasePtr>& vecItem) const;

	const MapItemDB& getMapItemDB() const
	{
		return m_mapItemDB;
	}

	template <typename TItem>
	void InsertItem(const std::string_view& strNameTag, Int32 ID, Int32 price)
	{
		std::shared_ptr<TItem> spItem = std::make_shared<TItem>();
		spItem->setNameTag(strNameTag);
		spItem->setID(ID);
		spItem->setPrice(price);

		m_mapItemDB.Subscribe(strNameTag.data(), spItem);
 	}

private:
	MapItemDB m_mapItemDB;
};

#endif