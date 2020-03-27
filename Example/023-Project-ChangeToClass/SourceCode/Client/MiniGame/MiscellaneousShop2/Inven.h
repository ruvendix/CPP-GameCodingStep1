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
	Inven();
	virtual ~Inven();
#pragma endregion

	void AddInvenItemInfo(const ItemBase* pItem);
	void DeleteInvenItemInfo(Int32 invenIdx);
	void Draw(Int32 x, Int32 y) const;
	void DrawForSell(Int32 x, Int32 y) const;
	void Arrange();
	bool IsFull() const;

	InvenItemInfo* FindInvenItemInfo(Int32 invenIdx) const;
	InvenItemInfo* FindInvenItemInfo(const std::string& strItemNameTag) const;

	Int32 getMaxInvenSize() const
	{
		return m_maxInvenSize;
	}

private:
	Int32 m_currentIdx = 0;
	Int32 m_maxInvenSize = 5; // �κ��� ���� �� �ִ� ������ 5��
	std::vector<InvenItemInfo*> m_vecInvenItemInfo;
};

#endif