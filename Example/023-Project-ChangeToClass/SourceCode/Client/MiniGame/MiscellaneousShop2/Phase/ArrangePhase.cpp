// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 정리 페이즈입니다.
// 정리 페이즈에서는 인벤토리를 정리할 수 있습니다.
// =====================================================================================

#include "PCH.h"
#include "ArrangePhase.h"

#include "Controller\InputController.h"
#include "Controller\ConsoleController.h"
#include "Manager\TriggerTimerManager.h"
#include "EntrancePhase.h"

#include "..\PlayerContext.h"
#include "..\Inven.h"

class ArrangePhaseHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(ArrangePhaseHelper);

public:
	static void ArrangeInven(_Out_ ArrangePhase& targetHelper);
	static void ResultArrangeInven();
};

void ArrangePhaseHelper::ArrangeInven(_Out_ ArrangePhase& targetHelper)
{
	const ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	Int32 result = consoleSelector.getSelectorPos().Y - consoleSelector.getMinSelectorPos().Y;	
	if (result == 1)
	{
		targetHelper.setNextPhase(trace_new EntrancePhase);
		return;
	}

	Inven* pInven = PlayerCtx::I()->getInven();
	CHECK_NULLPTR(pInven);
	pInven->Arrange();

	RESERVE_RENDERING_STRING(3.0f, &ArrangePhaseHelper::ResultArrangeInven);
}

void ArrangePhaseHelper::ResultArrangeInven()
{
	PRINTF(0, 17, "인벤토리가 정리되었습니다!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

EErrorType ArrangePhase::OnInitialize()
{
	InputController::I()->InsertInputMappingInfo("GotoEntrancPhase", VK_ESCAPE);
	InputController::I()->InsertInputMappingInfo("SelectUp", VK_UP);
	InputController::I()->InsertInputMappingInfo("SelectDown", VK_DOWN);
	InputController::I()->InsertInputMappingInfo("SelectMenu", VK_RETURN);

	setLevel(1);

	return EErrorType::NONE;
}

EErrorType ArrangePhase::OnPostInitialize()
{
	ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	consoleSelector.setSelectorPos(0, 14);
	consoleSelector.setMinSelectorPosY(14);
	consoleSelector.setMaxSelectorPosY(15);

	return EErrorType::NONE;
}

EErrorType ArrangePhase::OnInput()
{
	if (InputController::I()->CheckInputState("GotoEntrancPhase", EInputMappingState::DOWN) == true)
	{
		setNextPhase(trace_new EntrancePhase);
	}

	if (InputController::I()->CheckInputState("SelectUp", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(-1);
		DEBUG_LOG("SelectUp 눌렀다!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+1);
		DEBUG_LOG("SelectDown 눌렀다!");
	}

	if (InputController::I()->CheckInputState("SelectMenu", EInputMappingState::DOWN) == true)
	{
		ArrangePhaseHelper::ArrangeInven(*this);
		DEBUG_LOG("SelectMenu 눌렀다!");
	}	

	return EErrorType::NONE;
}

EErrorType ArrangePhase::OnRender()
{
	Inven* pInven = PlayerCtx::I()->getInven();
	CHECK_NULLPTR(pInven);
	pInven->Draw(0, 0);

	PRINTF(0, 12, "인벤토리를 정리하시겠습니까?");
	PRINTF(0, 14, "    예");
	PRINTF(0, 15, "    아니오");

	ConsoleController::I()->DrawSelector();
	return EErrorType::NONE;
}

EErrorType ArrangePhase::OnFinalize()
{
	return EErrorType::NONE;
}
