// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������ DB �����Դϴ�.
// ������ ��ȸ�� �� �̿��ϸ� �˴ϴ�.
// =====================================================================================

#ifndef ITEM_DB_CONTEXT_H__
#define ITEM_DB_CONTEXT_H__

#include "Common\CommonFunc.h"
#include "ItemDBEnum.h"

class ItemBase;
class ItemDB;

class ItemDBCtx final
{
	DECLARE_PHOENIX_SINGLETON(ItemDBCtx);

public:
	using ItemDBTable = std::array<ItemDB*, CommonFunc::ToUnderlyingType(EItemDBType::END)>;

	void Initialize();
	void Finalize();

	ItemBase* QueryItem(const std::string& strItemNameTag) const;	
	ItemDB* QueryItemDB(EItemDBType itemDBType) const;
	TSize QueryItemCntOfItemDB(EItemDBType itemDBType) const;

private:
	ItemDBTable m_itemDBTable;
};

#endif