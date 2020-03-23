// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �÷��̾��� �κ��丮�Դϴ�.
// ������ ���� �����۸� ������ �� �ֽ��ϴ�.
// ItemDB�ʹ� �ٸ��� vector�� �̿��մϴ�. (�κ��丮 ������ �����������Ƿ�!)
// =====================================================================================

#ifndef PLAYER_INVEN_H__
#define PLAYER_INVEN_H__

#include "Common\CommonType.h"
#include "Common\CommonNecessary.h"

class ItemBase;

struct InvenItemInfo
{
	ItemBase* pItem = nullptr;
	Int32 cnt = 0;
};

class Inven
{
public:
#pragma region ������ �� �Ҹ���
	Inven() = default;
	virtual ~Inven();
#pragma endregion

	InvenItemInfo* FindInvenItemInfo(const std::string& strItemNameTag) const;
	void AddInvenItemInfo(const ItemBase* pItem);
	void DeleteInvenItemInfo(const std::string& strItemNameTag);
	void DrawInven(Int32 x, Int32 y) const;
	void DrawInvenForSell(Int32 x, Int32 y) const;
	bool IsFull() const;

private:
	Int32 m_maxInvenSize = 5; // �κ��� ���� �� �ִ� ������ 5��
	std::vector<InvenItemInfo*> m_vecInvenItemInfo;
};

#endif