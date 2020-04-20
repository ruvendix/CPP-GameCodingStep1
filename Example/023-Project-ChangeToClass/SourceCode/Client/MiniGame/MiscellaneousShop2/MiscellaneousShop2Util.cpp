// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 잡화상점2의 유틸 함수 모음입니다.
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
		PUT_STRING(0, 0, "알 수 없는 아이템 DB에요!");
		return;
	}

	Int32 drawPosY = y - 1;
	PUT_STRING(x, ++drawPosY, "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━┓");
	PUT_STRING(x, ++drawPosY, "┃    이름                            ┃     가격┃");
	PUT_STRING(x, ++drawPosY, "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━┫");

	const MapItemDB& mapItemDB = pItemDB->getMapItemDB();
	for (const auto& iter : mapItemDB)
	{
		ItemBase* pItem = iter.second;
		if (pItem == nullptr)
		{
			continue;
		}

		PUT_STRING(x, ++drawPosY, "┃    %-32s┃ %8d┃", pItem->getNameTag().c_str(), pItem->getPrice());
	}

	PUT_STRING(x, ++drawPosY, "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━┛");
}
