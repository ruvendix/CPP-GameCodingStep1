// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������ �⺻���Դϴ�.
// ���������� �Ĵ� �����ۻӸ� �ƴ϶� ���� ���������� ���� �����մϴ�.
// =====================================================================================

#include "PCH.h"
#include "ItemBase.h"

ItemBase* ItemBase::Clone() const
{
	ItemBase* pItem = trace_new ItemBase;
	*pItem = *this;
	return pItem;
}
