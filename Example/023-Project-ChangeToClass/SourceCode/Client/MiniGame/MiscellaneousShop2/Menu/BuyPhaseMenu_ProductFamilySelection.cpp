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
