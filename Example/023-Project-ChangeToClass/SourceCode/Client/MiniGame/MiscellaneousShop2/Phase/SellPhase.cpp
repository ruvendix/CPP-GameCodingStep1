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
#include "Element\ConsoleSelector.h"
#include "EntrancePhase.h"

#include "..\PlayerContext.h"
#include "..\Inven.h"

EErrorType SellPhase::OnInitialize()
{
	InputController::I()->InsertInputMappingInfo("GotoEntrancPhase", VK_ESCAPE);
	InputController::I()->InsertInputMappingInfo("SelectUp", VK_UP);
	InputController::I()->InsertInputMappingInfo("SelectDown", VK_DOWN);
	InputController::I()->InsertInputMappingInfo("SelectLeft", VK_LEFT);
	InputController::I()->InsertInputMappingInfo("SelectRight", VK_RIGHT);
	InputController::I()->InsertInputMappingInfo("SellItem", VK_RETURN);

	setLevel(1);

	return EErrorType::NONE;
}

EErrorType SellPhase::OnPostInitialize()
{
	ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	consoleSelector.setSelectorPos(2, 3);
	consoleSelector.setMinSelectorPosY(3);

	Inven* pInven = PlayerCtx::I()->getInven();
	CHECK_NULLPTR(pInven);
	consoleSelector.setMaxSelectorPosY(3 + pInven->getMaxInvenSize() - 1);

	return EErrorType();
}

EErrorType SellPhase::OnUpdate()
{
	if (InputController::I()->CheckInputState("GotoEntrancPhase", EInputMappingState::DOWN) == true)
	{
		TriggerTimerMgr::I()->DeleteTriggerTimer("GameError");
		setNextPhase(trace_new EntrancePhase);
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

	BEGIN_FRAME_UPDATE_LIMITED();
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
	END_FRAME_UPDATE_LIMITED();

	if (InputController::I()->CheckInputState("SellItem", EInputMappingState::DOWN) == true)
	{
		//SellItem(targetHelper);
		DEBUG_LOG("SellItem ������!");
	}

	return EErrorType::NONE;
}

EErrorType SellPhase::OnRender()
{
	Inven* pInven = PlayerCtx::I()->getInven();
	CHECK_NULLPTR(pInven);
	pInven->DrawInvenForSell(0, 0);

	ConsoleController::I()->DrawSelector();
	return EErrorType::NONE;
}

EErrorType SellPhase::OnFinalize()
{

	return EErrorType::NONE;
}
