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
using ItemBasePtr = std::shared_ptr<ItemBase>;

struct InvenItemInfo
{
	ItemBasePtr spItem = nullptr;
	Int32 cnt = 0;
};

using InvenItemInfoPtr = std::shared_ptr<InvenItemInfo>;

class Inven final
{
public:
#pragma region ������ �� �Ҹ���
	Inven();
	~Inven() = default;
#pragma endregion

	void AddInvenItemInfo(ItemBasePtr spItem);
	void DeleteInvenItemInfo(Int32 invenIdx);
	void Draw(Int32 x, Int32 y) const;
	void DrawForSell(Int32 x, Int32 y) const;
	void Arrange();
	bool IsFull() const;

	InvenItemInfoPtr FindInvenItemInfo(Int32 invenIdx) const;
	InvenItemInfoPtr FindInvenItemInfo(const std::string& strItemNameTag) const;

	Int32 getMaxInvenSize() const
	{
		return m_maxInvenSize;
	}

private:
	Int32 m_currentIdx = 0;
	Int32 m_maxInvenSize = 5; // �κ��� ���� �� �ִ� ������ 5��
	std::vector<InvenItemInfoPtr> m_vecInvenItemInfo;
};

#endif