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
#include "Manager\PhaseManager.h"
#include "EntrancePhase.h"

#include "..\PlayerContext.h"
#include "..\Inven.h"

class ArrangePhaseHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(ArrangePhaseHelper);

public:
	static void ArrangeInven(_Out_ ArrangePhase& targetHelper);
	static void ArrangeInvenComplete();
};

void ArrangePhaseHelper::ArrangeInven(_Out_ ArrangePhase& targetHelper)
{
	const ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	Int32 ret = consoleSelector.getSelectorPos().Y - consoleSelector.getMinSelectorPos().Y;	
	if (ret == 1)
	{
		PhaseMgr::I()->CreatePhase<EntrancePhase>(ECreateType::NEXT, 0);
		return;
	}

	PlayerCtx::I()->getInven()->Arrange();
	RESERVE_RENDERING_STRING(3.0f, &ArrangePhaseHelper::ArrangeInvenComplete);
}

void ArrangePhaseHelper::ArrangeInvenComplete()
{
	PUT_STRING(0, 17, "인벤토리가 정리되었습니다!");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

EErrorType ArrangePhase::OnInitialize()
{
	InputController::I()->InsertInputMappingInfo("GotoEntrancPhase", VK_ESCAPE);
	InputController::I()->InsertInputMappingInfo("SelectUp", VK_UP);
	InputController::I()->InsertInputMappingInfo("SelectDown", VK_DOWN);
	InputController::I()->InsertInputMappingInfo("SelectMenu", VK_RETURN);

	ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	consoleSelector.setSelectorPos(0, 14);
	consoleSelector.setMinSelectorPosY(14);
	consoleSelector.setMaxSelectorPosY(15);

	return EErrorType::NOTHING;
}

EErrorType ArrangePhase::OnInput()
{
	if (GameElem::OnInput() == EErrorType::FIRST_INPUT)
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

	return EErrorType::NOTHING;
}

EErrorType ArrangePhase::OnRender()
{
	PlayerCtx::I()->getInven()->Draw(0, 0);

	PUT_STRING(0, 12, "인벤토리를 정리하시겠습니까?");
	PUT_STRING(0, 14, "    예");
	PUT_STRING(0, 15, "    아니오");

	ConsoleController::I()->DrawSelector();
	return EErrorType::NOTHING;
}