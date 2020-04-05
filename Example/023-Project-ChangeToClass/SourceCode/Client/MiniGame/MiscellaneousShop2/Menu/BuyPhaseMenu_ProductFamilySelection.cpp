// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 구매 페이즈에서 사용되는 메뉴입니다.
// 선택된 제품군의 정보를 보여줍니다.
// =====================================================================================

#include "PCH.h"
#include "BuyPhaseMenu_ProductFamilySelection.h"

#include "Controller\ConsoleController.h"

#include "..\Phase\BuyPhase.h"
#include "..\Item\ItemDBContext.h"
#include "..\Item\ItemDB.h"

BuyPhaseMenu_ProductFamilySelection::BuyPhaseMenu_ProductFamilySelection(const std::string_view& szNameTag,
	const COORD& pos, EItemDBType itemDBType, BuyPhase* pBuyPhase) :
	Menu(szNameTag, pos),
	m_itemDBType(itemDBType),
	m_pBuyPhase(pBuyPhase)
{

}

EErrorType BuyPhaseMenu_ProductFamilySelection::OnExcute()
{
	CHECK_NULLPTR(m_pBuyPhase);
	m_pBuyPhase->SelectedProductFamily(true);

	ConsoleController::I()->PushBackupConsoleSelector();

	m_pBuyPhase->setCurrentItemDBType(m_itemDBType);
	ItemDB* pItemDB = ItemDBCtx::I()->QueryItemDB(m_itemDBType);
	CHECK_NULLPTR(pItemDB);

	TSize itemCnt = pItemDB->getMapItemDB().size();

	std::vector<ItemBase*> vecItem;
	m_pBuyPhase->ResetDisplayItem(itemCnt);
	pItemDB->CopyToVector(m_pBuyPhase->getVecDisplayItem());

	ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	consoleSelector.setMinSelectorPosY(3);
	consoleSelector.setMaxSelectorPosY(3 + itemCnt - 1);
	consoleSelector.setSelectorPos(2, 3);

	return EErrorType();
}
