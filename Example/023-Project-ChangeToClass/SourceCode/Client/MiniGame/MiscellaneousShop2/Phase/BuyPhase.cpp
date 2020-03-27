// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 구매 페이즈입니다.
// 구매 페이즈에서는 상점 아이템을 구매할 수 있습니다.
// =====================================================================================

#include "PCH.h"
#include "BuyPhase.h"

#include "Controller\InputController.h"
#include "Controller\ConsoleController.h"
#include "Controller\FrameController.h"
#include "Manager\TriggerTimerManager.h"
#include "Element\ConsoleSelector.h"
#include "EntrancePhase.h"

#include "..\PlayerContext.h"
#include "..\Inven.h"
#include "..\Item\ItemDBContext.h"
#include "..\Item\ItemDB.h"
#include "..\Item\ItemBase.h"
#include "..\MiscellaneousShop2Util.h"

class BuyPhaseHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(BuyPhaseHelper);

public:
	static EItemDBType ToItemDBType(const COORD& selectorPos);
	static void BuyItem(const BuyPhase& targetHelper);
	static void ResultBuyItem();

	static void OnInput_ProductFamily(_Inout_ BuyPhase& targetHelper);
	static void OnInput_SelectedProductFamily(_Inout_ BuyPhase& targetHelper);
};

EItemDBType BuyPhaseHelper::ToItemDBType(const COORD& selectorPos)
{
	if ( (selectorPos.X == 2) && 
		 (selectorPos.Y == 3) )
	{
		return EItemDBType::POTION;
	}

	if ( (selectorPos.X == 19) && 
		 (selectorPos.Y == 3) )
	{
		return EItemDBType::GROCERY;
	}

	if ( (selectorPos.X == 2) && 
		 (selectorPos.Y == 5) )
	{
		return EItemDBType::CAMPING;
	}

	if ( (selectorPos.X == 19) && 
		 (selectorPos.Y == 5) )
	{
		return EItemDBType::NONE;
	}

	return EItemDBType::NONE;
}

void BuyPhaseHelper::BuyItem(const BuyPhase& targetHelper)
{
	const ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	Int32 selectedIdx = consoleSelector.getSelectorPos().Y - consoleSelector.getMinSelectorPos().Y;
	ItemBase* pItem = targetHelper.m_vecDisplayItem.at(selectedIdx);
	CHECK_NULLPTR(pItem);

	Inven* pInven = PlayerCtx::I()->getInven();
	CHECK_NULLPTR(pInven);

	// 이미 인벤에 있는 아이템인지 확인!
	if ( (pInven->FindInvenItemInfo(pItem->getNameTag()) == nullptr) &&
		 (pInven->IsFull()) )
	{
		DEFAULT_ERROR_HANDLER_RENDERING(0, 12, 3.0f, EErrorType::FULL_INVEN);
		return;
	}

	Int32 playerGameMoney = PlayerCtx::I()->getGameMoney();
	Int32 itemPrice = pItem->getPrice();

	// 가격 확인
	if (playerGameMoney < pItem->getPrice())
	{
		DEFAULT_ERROR_HANDLER_RENDERING(0, 12, 3.0f, EErrorType::NOT_ENOUGH_GAME_MONEY, playerGameMoney, itemPrice);
		return;
	}
	else
	{
		playerGameMoney -= itemPrice;
		PlayerCtx::I()->setGameMoney(playerGameMoney);
	}

	// 위에서 이미 확인했지만 내부에서도 또 확인해요...
	pInven->AddInvenItemInfo(pItem);
	RESERVE_RENDERING_STRING(3.0f, &BuyPhaseHelper::ResultBuyItem);
}

void BuyPhaseHelper::ResultBuyItem()
{
	PRINTF(0, 12, "아이템을 구매했습니다!");
}

void BuyPhaseHelper::OnInput_ProductFamily(_Inout_ BuyPhase& targetHelper)
{
	if (InputController::I()->CheckInputState("GotoEntrancPhase", EInputMappingState::DOWN) == true)
	{
		targetHelper.setNextPhase(trace_new EntrancePhase);
	}

	if (InputController::I()->CheckInputState("SelectLeft", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosX(-17);
		DEBUG_LOG("SelectLeft 눌렀다!");
	}

	if (InputController::I()->CheckInputState("SelectRight", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosX(+17);
		DEBUG_LOG("SelectRight 눌렀다!");
	}

	if (InputController::I()->CheckInputState("SelectUp", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(-2);
		DEBUG_LOG("SelectUp 눌렀다!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+2);
		DEBUG_LOG("SelectDown 눌렀다!");
	}

	if (InputController::I()->CheckInputState("SelectMenu", EInputMappingState::DOWN) == true)
	{
		ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
		targetHelper.m_itemDBType = ToItemDBType(consoleSelector.getSelectorPos());
		if (targetHelper.m_itemDBType == EItemDBType::NONE)
		{
			targetHelper.setNextPhase(trace_new EntrancePhase);
		}
		else
		{
			targetHelper.m_bSelectedProductFamily = true;
			ConsoleController::I()->PushBackupConsoleSelector();

			ItemDB* pItemDB = ItemDBCtx::I()->QueryItemDB(targetHelper.m_itemDBType);
			CHECK_NULLPTR(pItemDB);

			TSize itemCnt = pItemDB->getMapItemDB().size();

			std::vector<ItemBase*> vecItem;
			targetHelper.m_vecDisplayItem.clear();
			targetHelper.m_vecDisplayItem.reserve(itemCnt);
			pItemDB->CopyToVector(targetHelper.m_vecDisplayItem);

			consoleSelector.setMinSelectorPosY(3);
			consoleSelector.setMaxSelectorPosY(3 + itemCnt - 1);
			consoleSelector.setSelectorPos(2, 3);
		}

		DEBUG_LOG("SelectMenu 눌렀다!");
	}
}

void BuyPhaseHelper::OnInput_SelectedProductFamily(_Inout_ BuyPhase& targetHelper)
{
	if (InputController::I()->CheckInputState("GotoProductFamily", EInputMappingState::DOWN) == true)
	{
		TriggerTimerMgr::I()->DeleteTriggerTimer("RenderString");

		targetHelper.m_bSelectedProductFamily = false;
		ConsoleController::I()->RestoreConsoleSelector();
	}

	if (InputController::I()->CheckInputState("SelectUp", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(-1);
		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("SelectUp 눌렀다!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+1);
		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("SelectDown 눌렀다!");
	}

	BEGIN_INPUT_FPS_LIMITED_HELPER(targetHelper);
	if (InputController::I()->CheckInputState("SelectUp", EInputMappingState::PRESSING) == true)
	{
		ConsoleController::I()->AddSelectorPosY(-1);
		DEBUG_LOG("SelectUp 누르는 중!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::PRESSING) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+1);
		DEBUG_LOG("SelectDown 누르는 중!");
	}
	END_INPUT_FPS_LIMITED();

	if (InputController::I()->CheckInputState("BuyItem", EInputMappingState::DOWN) == true)
	{
		BuyItem(targetHelper);
		DEBUG_LOG("SelectMenu 눌렀다!");
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

EErrorType BuyPhase::OnPostInitialize()
{
	ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	consoleSelector.setSelectorPos(2, 3);
	consoleSelector.setMinSelectorPosY(3);
	consoleSelector.setMaxSelectorPosY(5);

	return EErrorType::NONE;
}

EErrorType BuyPhase::OnInitialize()
{
	InputController::I()->InsertInputMappingInfo("GotoEntrancPhase", VK_ESCAPE);
	InputController::I()->InsertInputMappingInfo("GotoProductFamily", VK_ESCAPE);
	InputController::I()->InsertInputMappingInfo("SelectUp", VK_UP);
	InputController::I()->InsertInputMappingInfo("SelectDown", VK_DOWN);
	InputController::I()->InsertInputMappingInfo("SelectLeft", VK_LEFT);
	InputController::I()->InsertInputMappingInfo("SelectRight", VK_RIGHT);
	InputController::I()->InsertInputMappingInfo("SelectMenu", VK_RETURN);
	InputController::I()->InsertInputMappingInfo("BuyItem", VK_RETURN);
	
	setLevel(1);

	return EErrorType::NONE;
}

EErrorType BuyPhase::OnInput()
{
	if (m_bSelectedProductFamily == false)
	{
		BuyPhaseHelper::OnInput_ProductFamily(*this);
	}
	else
	{
		BuyPhaseHelper::OnInput_SelectedProductFamily(*this);
	}

	return EErrorType::NONE;
}

EErrorType BuyPhase::OnRender()
{
	if (m_bSelectedProductFamily == false)
	{
		Int32 drawPosY = -1;
		PRINTF(0, ++drawPosY, "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
		PRINTF(0, ++drawPosY, "┃ 어떤 아이템에 관심 있으세요?    ┃");
		PRINTF(0, ++drawPosY, "┣━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━┫");
		PRINTF(0, ++drawPosY, "┃    물약        ┃    식료품      ┃");
		PRINTF(0, ++drawPosY, "┣━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━┫");
		PRINTF(0, ++drawPosY, "┃    야외용품    ┃    뒤로        ┃");
		PRINTF(0, ++drawPosY, "┗━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━┛");
	}
	else
	{
		MiscellanouseShop2Util::DrawItemTable(0, 0, m_itemDBType);

		Inven* pInven = PlayerCtx::I()->getInven();
		CHECK_NULLPTR(pInven);
		pInven->Draw(50, 0);
	}

	ConsoleController::I()->DrawSelector();

	return EErrorType::NONE;
}

EErrorType BuyPhase::OnFinalize()
{
	return EErrorType::NONE;
}
