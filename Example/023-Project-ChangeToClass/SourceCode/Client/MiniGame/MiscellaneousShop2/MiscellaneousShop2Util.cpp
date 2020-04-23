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

void MiscellanouseShop2Util::DrawItemTable(Int32 x, Int32 y, EItemDBType type)
{
	Int32 drawPosY = y - 1;
	PUT_STRING(x, ++drawPosY, "������������������������������������������������������������������������������������������������");
	PUT_STRING(x, ++drawPosY, "��    �̸�                            ��     ���ݦ�");
	PUT_STRING(x, ++drawPosY, "������������������������������������������������������������������������������������������������");

	const MapItemDB& mapItemDB = ItemDBCtx::I()->FindItemDB(type)->getMapItemDB();
	for (const auto& iter : mapItemDB.getMap())
	{
		ItemBasePtr spItem = iter.second;
		PUT_STRING(x, ++drawPosY, "��    %-32s�� %8d��", spItem->getNameTag().c_str(), spItem->getPrice());
	}

	PUT_STRING(x, ++drawPosY, "������������������������������������������������������������������������������������������������");
}
