// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �������Դϴ�.
// ���� ��������� ���� �������� ������ �� �ֽ��ϴ�.
// =====================================================================================

#include "PCH.h"
#include "BuyPhase.h"

#include "Controller\InputController.h"
#include "Controller\ConsoleController.h"
#include "Controller\FrameController.h"
#include "Manager\TriggerTimerManager.h"
#include "Manager\PhaseManager.h"
#include "Element\ConsoleSelector.h"
#include "EntrancePhase.h"

#include "..\PlayerContext.h"
#include "..\Inven.h"
#include "..\Item\ItemDBContext.h"
#include "..\Item\ItemDB.h"
#include "..\Item\ItemBase.h"
#include "..\MiscellaneousShop2Util.h"
#include "..\Menu\BuyPhaseMenu_ProductFamilySelection.h"
#include "..\Menu\EntrancePhaseMenu_PhaseLoader.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace
{
	std::unique_ptr<UI_PosInfo> s_spUI_posInfo;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class BuyPhaseHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(BuyPhaseHelper);

public:
	static void DrawMenu(const COORD& pos, std::shared_ptr<MenuTable_Mat> spMenuTable);

	static EItemDBType ToItemDBType(const COORD& selectorPos);
	static void BuyItem(const BuyPhase& targetHelper);
	static void BuyItemComplete();

	static void OnInput_ProductFamily(_Inout_ BuyPhase& targetHelper);
	static void OnInput_SelectedProductFamily(_Inout_ BuyPhase& targetHelper);
};

void BuyPhaseHelper::DrawMenu(const COORD& pos, std::shared_ptr<MenuTable_Mat> spMenuTable)
{
	Int32 drawPosY = pos.Y;
	PUT_STRING(pos.X,   drawPosY, "����������������������������������������������������������������������");
	PUT_STRING(pos.X, ++drawPosY, "�� � �����ۿ� ���� ��������?    ��");
	PUT_STRING(pos.X, ++drawPosY, "����������������������������������������������������������������������");
	PUT_STRING(pos.X, ++drawPosY, "��                ��                ��");
	PUT_STRING(pos.X, ++drawPosY, "����������������������������������������������������������������������");
	PUT_STRING(pos.X, ++drawPosY, "��                ��                ��");
	PUT_STRING(pos.X, ++drawPosY, "����������������������������������������������������������������������");

	spMenuTable->DrawMenu();
}

void BuyPhaseHelper::BuyItem(const BuyPhase& targetHelper)
{
	const ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	Int32 selectedIdx = consoleSelector.getSelectorPos().Y - consoleSelector.getMinSelectorPos().Y;
	ItemBase* pItem = targetHelper.m_vecDisplayItem.at(selectedIdx);
	CHECK_NULLPTR(pItem);

	Inven* pInven = PlayerCtx::I()->getInven();
	CHECK_NULLPTR(pInven);

	// �̹� �κ��� �ִ� ���������� Ȯ��!
	if ( (pInven->FindInvenItemInfo(pItem->getNameTag()) == nullptr) &&
		 (pInven->IsFull()) )
	{
		DEFAULT_ERROR_HANDLER_RENDERING(0, 12, 3.0f, EErrorType::FULL_INVEN);
		return;
	}

	Int32 playerGameMoney = PlayerCtx::I()->getGameMoney();
	Int32 itemPrice = pItem->getPrice();

	// ���� Ȯ��
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

	// ������ �̹� Ȯ�������� ���ο����� �� Ȯ���ؿ�...
	pInven->AddInvenItemInfo(pItem);
	RESERVE_RENDERING_STRING(3.0f, &BuyPhaseHelper::BuyItemComplete);
}

void BuyPhaseHelper::BuyItemComplete()
{
	PUT_STRING(0, 12, "�������� �����߽��ϴ�!");
}

void BuyPhaseHelper::OnInput_ProductFamily(_Inout_ BuyPhase& targetHelper)
{
	targetHelper.m_spMenuTable->OnInput();

	if (InputController::I()->CheckInputState("GotoEntrancPhase", EInputMappingState::DOWN) == true)
	{
		targetHelper.m_spMenuTable->getLastMenu()->OnExcute();
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
		DEBUG_LOG("SelectUp ������!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+1);
		targetHelper.m_localTime = 0.0f;
		DEBUG_LOG("SelectDown ������!");
	}

	BEGIN_INPUT_FPS_LIMITED_HELPER(targetHelper);
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

	if (InputController::I()->CheckInputState("BuyItem", EInputMappingState::DOWN) == true)
	{
		BuyItem(targetHelper);
		DEBUG_LOG("SelectMenu ������!");
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

EErrorType BuyPhase::OnInitialize()
{
	InputController::I()->InsertInputMappingInfo("GotoEntrancPhase", VK_ESCAPE);
	InputController::I()->InsertInputMappingInfo("GotoProductFamily", VK_ESCAPE);
	InputController::I()->InsertInputMappingInfo("SelectUp", VK_UP);
	InputController::I()->InsertInputMappingInfo("SelectDown", VK_DOWN);
	InputController::I()->InsertInputMappingInfo("BuyItem", VK_RETURN);

	s_spUI_posInfo = std::make_unique<UI_PosInfo>();
	s_spUI_posInfo->startPos = COORD{ 0, 0 };
	s_spUI_posInfo->menuStartPos = s_spUI_posInfo->startPos;
	s_spUI_posInfo->menuStartPos.X += ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_MENU;
	s_spUI_posInfo->menuStartPos.Y += 3;
	s_spUI_posInfo->diffSize = SizeInfo{ 17, 2 };
	
	m_spMenuTable = std::make_shared<MenuTable_Mat>(2, 2);
	m_spMenuTable->AddForMat(std::make_shared<BuyPhaseMenu_ProductFamilySelection>("����",
		COORD{ s_spUI_posInfo->menuStartPos.X, s_spUI_posInfo->menuStartPos.Y }, EItemDBType::POTION, this), 0, 0);

	m_spMenuTable->AddForMat(std::make_shared<BuyPhaseMenu_ProductFamilySelection>("�ķ�ǰ",
		COORD{ s_spUI_posInfo->menuStartPos.X + static_cast<SHORT>(s_spUI_posInfo->diffSize.width),
		s_spUI_posInfo->menuStartPos.Y }, EItemDBType::GROCERY, this), 0, 1);

	m_spMenuTable->AddForMat(std::make_shared<BuyPhaseMenu_ProductFamilySelection>("�߿ܿ�ǰ",
		COORD{ s_spUI_posInfo->menuStartPos.X,
		s_spUI_posInfo->menuStartPos.Y + static_cast<SHORT>(s_spUI_posInfo->diffSize.height) }, EItemDBType::CAMPING, this), 1, 0);

	m_spMenuTable->AddForMat(std::make_shared<EntrancePhaseMenu_PhaseLoader>("�ڷ� ����",
		COORD{ s_spUI_posInfo->menuStartPos.X + static_cast<SHORT>(s_spUI_posInfo->diffSize.width),
		s_spUI_posInfo->menuStartPos.Y + static_cast<SHORT>(s_spUI_posInfo->diffSize.height) },
		EMiscellaneousShop2PhaseType::ENTRANCE), 1, 1);

	ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	consoleSelector.setSelectorPos(
		s_spUI_posInfo->startPos.X + ConsoleSelector::SELECTOR_LEFT_MARGIN_ON_BORDER, s_spUI_posInfo->menuStartPos.Y);

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
		BuyPhaseHelper::DrawMenu(s_spUI_posInfo->startPos, m_spMenuTable);
	}
	else
	{
		MiscellanouseShop2Util::DrawItemTable(0, 0, m_currentItemDBType);

		Inven* pInven = PlayerCtx::I()->getInven();
		CHECK_NULLPTR(pInven);
		pInven->Draw(50, 0);
	}

	ConsoleController::I()->DrawSelector();

	return EErrorType::NONE;
}