// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��ȭ����2�� ��ƿ �Լ� �����Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "MiscellaneousShop2Util.h"

#include "Controller\ConsoleController.h"
#include "Item\ItemDBContext.h"
#include "Item\ItemDB.h"
#include "Item\ItemBase.h"
#include "PlayerContext.h"

void MiscellanouseShop2Util::DrawItemTable(Int32 x, Int32 y, EItemDBType itemDBType)
{
	ItemDB* pItemDB = ItemDBCtx::I()->QueryItemDB(itemDBType);	
	if (pItemDB == nullptr)
	{
		PUT_STRING(0, 0, "�� �� ���� ������ DB����!");
		return;
	}

	Int32 drawPosY = y - 1;
	PUT_STRING(x, ++drawPosY, "������������������������������������������������������������������������������������������������");
	PUT_STRING(x, ++drawPosY, "��    �̸�                            ��     ���ݦ�");
	PUT_STRING(x, ++drawPosY, "������������������������������������������������������������������������������������������������");

	const MapItemDB& mapItemDB = pItemDB->getMapItemDB();
	for (const auto& iter : mapItemDB)
	{
		ItemBase* pItem = iter.second;
		if (pItem == nullptr)
		{
			continue;
		}

		PUT_STRING(x, ++drawPosY, "��    %-32s�� %8d��", pItem->getNameTag().c_str(), pItem->getPrice());
	}

	PUT_STRING(x, ++drawPosY, "������������������������������������������������������������������������������������������������");
}
