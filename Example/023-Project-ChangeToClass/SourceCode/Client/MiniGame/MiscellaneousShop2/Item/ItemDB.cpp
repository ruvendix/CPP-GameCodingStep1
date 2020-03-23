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

ItemDB::~ItemDB()
{
	for (auto iter : m_mapItem)
	{
		SAFE_DELETE(iter.second);
	}
}

ItemBase* ItemDB::FindItem(const std::string& strNameTag) const
{
	auto iter = m_mapItem.find(strNameTag);
	if (iter != m_mapItem.end())
	{
		return (iter->second);
	}

	return nullptr;
}

void ItemDB::CopyToVector(std::vector<ItemBase*>& vecItem) const
{
	std::transform(m_mapItem.cbegin(), m_mapItem.cend(), std::back_inserter(vecItem), GetSecond(m_mapItem));
}
