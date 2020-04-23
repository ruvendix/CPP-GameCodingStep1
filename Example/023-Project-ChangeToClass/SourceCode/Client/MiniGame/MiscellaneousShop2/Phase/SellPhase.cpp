// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �Ǹ� �������Դϴ�.
// �Ǹ� ��������� �������� �Ǹ��� �� �ֽ��ϴ�.
// =====================================================================================

#include "PCH.h"
#include "SellPhase.h"

#include "Controller\InputController.h"
#include "Controller\ConsoleController.h"
#include "Controller\FrameController.h"
#include "Manager\TriggerTimerManager.h"
#include "Manager\PhaseManager.h"
#include "Element\ConsoleSelector.h"
#include "EntrancePhase.h"

#include "..\PlayerContext.h"
#include "..\Inven.h"
#include "..\Item\ItemBase.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

using InvenPtr = std::shared_ptr<Inven>;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SellPhaseHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(SellPhaseHelper);

public:
	static void SellItem(const SellPhase& targetHelper);
	static void SellItemComplete();
};

void SellPhaseHelper::SellItem(const SellPhase& targetHelper)
{
	const ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	Int32 selectedIdx = consoleSelector.getSelectorPos().Y - consoleSelector.getMinSelectorPos().Y;

	InvenPtr spInven = PlayerCtx::I()->getInven();
	InvenItemInfoPtr spInvenItemInfo = spInven->FindInvenItemInfo(selectedIdx);

	if ( (spInvenItemInfo == nullptr) ||
		 (spInvenItemInfo->cnt <= 0) )
	{
		DEFAULT_ERROR_HANDLER_RENDERING(0, 12, 3.0f, EErrorType::NO_ITEM_IN_INVEN);
		return;
	}

	Int32 itemPrice = static_cast<Int32>(spInvenItemInfo->spItem->getPrice() * 0.8f);
	PlayerCtx::I()->AddGameMoney(itemPrice);
	--(spInvenItemInfo->cnt);

	if (spInvenItemInfo->cnt <= 0)
	{
		spInven->DeleteInvenItemInfo(selectedIdx);
	}

	RESERVE_RENDERING_STRING(3.0f, &SellPhaseHelper::SellItemComplete);
}

void SellPhaseHelper::SellItemComplete()
{
	PUT_STRING(0, 12, "�������� �Ǹ��߽��ϴ�!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

EErrorType SellPhase::OnInitialize()
{
	InputController::I()->InsertInputMappingInfo("GotoEntrancPhase", VK_ESCAPE);
	InputController::I()->InsertInputMappingInfo("SelectUp", VK_UP);
	InputController::I()->InsertInputMappingInfo("SelectDown", VK_DOWN);
	InputController::I()->InsertInputMappingInfo("SelectLeft", VK_LEFT);
	InputController::I()->InsertInputMappingInfo("SelectRight", VK_RIGHT);
	InputController::I()->InsertInputMappingInfo("SellItem", VK_RETURN);

	ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	consoleSelector.setSelectorPos(2, 3);
	consoleSelector.setMinSelectorPosY(3);

	consoleSelector.setMaxSelectorPosY(consoleSelector.getMinSelectorPos().Y + PlayerCtx::I()->getInven()->getMaxInvenSize() - 1);
	return EErrorType::NOTHING;
}

EErrorType SellPhase::OnInput()
{
	if (Phase::OnInput() == EErrorType::FIRST_INPUT)
	{
		return EErrorType::FIRST_INPUT;
	}

	if (InputController::I()->CheckInputState("GotoEntrancPhase", EInputMappingState::DOWN) == true)
	{
		PhaseMgr::I()->CreatePhase<EntrancePhase>(ECreateType::NEXT, 0);
	}

	if (InputController::I()->CheckInputState("SelectUp", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(-1);
		m_localTime = 0.0f;
		DEBUG_LOG("SelectUp ������!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+1);
		m_localTime = 0.0f;
		DEBUG_LOG("SelectDown ������!");
	}

	BEGIN_INPUT_FPS_LIMITED();
	if (InputController::I()->CheckInputState("SelectUp", EInputMappingState::PRESSING) == true)
	{
		ConsoleController::I()->AddSelectorPosY(-1);
		DEBUG_LOG("SelectUp ������ ��!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::PRESSING) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+1);
		DEBUG_LOG("SelectDown ������ ��!");
	}
	END_INPUT_FPS_LIMITED();

	if (InputController::I()->CheckInputState("SellItem", EInputMappingState::DOWN) == true)
	{
		SellPhaseHelper::SellItem(*this);
		DEBUG_LOG("SellItem ������!");
	}

	return EErrorType::NOTHING;
}

EErrorType SellPhase::OnRender()
{
	PlayerCtx::I()->getInven()->DrawForSell(0, 0);
	ConsoleController::I()->DrawSelector();

	return EErrorType::NOTHING;
}