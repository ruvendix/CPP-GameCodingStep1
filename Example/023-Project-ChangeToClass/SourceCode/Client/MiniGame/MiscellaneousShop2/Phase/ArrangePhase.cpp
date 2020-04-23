// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �������Դϴ�.
// ���� ��������� �κ��丮�� ������ �� �ֽ��ϴ�.
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
	PUT_STRING(0, 17, "�κ��丮�� �����Ǿ����ϴ�!");
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
		DEBUG_LOG("SelectUp ������!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+1);
		DEBUG_LOG("SelectDown ������!");
	}

	if (InputController::I()->CheckInputState("SelectMenu", EInputMappingState::DOWN) == true)
	{
		ArrangePhaseHelper::ArrangeInven(*this);
		DEBUG_LOG("SelectMenu ������!");
	}	

	return EErrorType::NOTHING;
}

EErrorType ArrangePhase::OnRender()
{
	PlayerCtx::I()->getInven()->Draw(0, 0);

	PUT_STRING(0, 12, "�κ��丮�� �����Ͻðڽ��ϱ�?");
	PUT_STRING(0, 14, "    ��");
	PUT_STRING(0, 15, "    �ƴϿ�");

	ConsoleController::I()->DrawSelector();
	return EErrorType::NOTHING;
}