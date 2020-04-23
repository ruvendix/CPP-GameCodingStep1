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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ItemDBPtr = std::shared_ptr<ItemDB>;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

BuyPhaseMenu_ProductFamilySelection::BuyPhaseMenu_ProductFamilySelection(const std::string_view& szNameTag,
	const COORD& pos, EItemDBType itemDBType, BuyPhase* pTargetPhase) :
	Menu(szNameTag, pos),
	m_itemDBType(itemDBType),
	m_pTargetPhase(pTargetPhase)
{

}

EErrorType BuyPhaseMenu_ProductFamilySelection::OnExcute()
{
	CHECK_NULLPTR(m_pTargetPhase);
	m_pTargetPhase->SelectedProductFamily(true);

	ConsoleController::I()->PushBackupConsoleSelector();
	m_pTargetPhase->setCurrentItemDBType(m_itemDBType);

	ItemDBPtr spItemDB = ItemDBCtx::I()->FindItemDB(m_itemDBType);
	TSize itemCnt = spItemDB->getMapItemDB().Size();

	std::vector<ItemBase*> vecItem;
	m_pTargetPhase->ResetDisplayItem(itemCnt);
	spItemDB->CopyToVector(m_pTargetPhase->getVecDisplayItem());

	ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	consoleSelector.setMinSelectorPosY(3);
	consoleSelector.setMaxSelectorPosY(3 + itemCnt - 1);
	consoleSelector.setSelectorPos(2, 3);

	return EErrorType();
}
