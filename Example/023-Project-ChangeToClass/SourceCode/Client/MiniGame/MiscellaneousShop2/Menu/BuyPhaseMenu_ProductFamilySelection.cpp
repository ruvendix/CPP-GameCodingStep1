// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ������� ���Ǵ� �޴��Դϴ�.
// ���õ� ��ǰ���� ������ �����ݴϴ�.
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
