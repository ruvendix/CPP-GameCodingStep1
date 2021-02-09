// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������ �����Դϴ�. �̷� �� �����ͺ��̽�, DB��� ����.
// �ϳ��� ��Ƶ� ������ �Ϲ������� DB�� ���� ���� �и��Ǿ��־��.
// =====================================================================================

#include "PCH.h"
#include "ItemDB.h"

#include "ItemBase.h"

ItemBasePtr ItemDB::FindItem(const std::string& strNameTag) const
{
	return m_mapItemDB.Find(strNameTag);
}

void ItemDB::CopyToVector(_Out_ std::vector<ItemBasePtr>& vecItem) const
{
	const MapItemDB::MapType& mapItem = m_mapItemDB.getMap();
	std::transform(mapItem.cbegin(), mapItem.cend(), std::back_inserter(vecItem), common_func::GetSecond(mapItem));
}
