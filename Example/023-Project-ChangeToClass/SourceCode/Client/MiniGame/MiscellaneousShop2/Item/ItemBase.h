// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������ �⺻���Դϴ�.
// ���������� �Ĵ� �����ۻӸ� �ƴ϶� ���� ���������� ���� �����մϴ�.
// =====================================================================================

#ifndef ITEM_BASE_H__
#define ITEM_BASE_H__

#include "Common\CommonType.h"
#include "Common\CommonMacro.h"
#include "Element\NameTag.h"

class ItemBase
{
	HAS_NAME_TAG();

public:
#pragma region ������ �� �Ҹ���
	ItemBase() = default;
	virtual ~ItemBase() = default;
#pragma endregion

	ItemBase* Clone() const;

	Int32 getID() const
	{
		return m_ID;
	}

	Int32 getPrice() const
	{
		return m_price;
	}

	void setID(Int32 ID)
	{
		m_ID = ID;
	}

	void setPrice(Int32 price)
	{
		m_price = price;
	}

private:
	Int32 m_ID = 0;
	Int32 m_price = 0;
};

#endif