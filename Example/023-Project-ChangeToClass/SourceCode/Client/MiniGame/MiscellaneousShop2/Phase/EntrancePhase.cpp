// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �������Դϴ�.
// ���� ��������� �ٸ� ����� ������ �� �ֽ��ϴ�.
// =====================================================================================

#include "PCH.h"
#include "EntrancePhase.h"

#include "Controller\ConsoleController.h"
#include "Controller\InputController.h"
#include "Manager\SceneManager.h"
#include "Element\ConsoleSelector.h"
#include "Element\Scene\IntroMenuScene.h"
#include "BuyPhase.h"
#include "SellPhase.h"
#include "ArrangePhase.h"

class EntrancePhaseHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(EntrancePhaseHelper);

public:
	static EPhaseType ToPhaseType(const COORD& selectorPos);
	static PhaseBase* CreateNextPhase(EPhaseType phaseType);
};

EPhaseType EntrancePhaseHelper::ToPhaseType(const COORD& selectorPos)
{
	if ( (selectorPos.X == 2) && 
		 (selectorPos.Y == 4) )
	{
		return EPhaseType::BUY;
	}

	if ( (selectorPos.X == 19) && 
		 (selectorPos.Y == 4) )
	{
		return EPhaseType::SELL;
	}

	if ( (selectorPos.X == 2) && 
		 (selectorPos.Y == 6) )
	{
		return EPhaseType::ARRANGE;
	}

	if ( (selectorPos.X == 19) && 
		 (selectorPos.Y == 6) )
	{
		return EPhaseType::NONE;
	}

	return EPhaseType::NONE;
}

PhaseBase* EntrancePhaseHelper::CreateNextPhase(EPhaseType phaseType)
{
	switch (phaseType)
	{
	case EPhaseType::BUY:
	{
		return (trace_new BuyPhase);
	}

	case EPhaseType::SELL:
	{
		return (trace_new SellPhase);
	}

	case EPhaseType::ARRANGE:
	{
		return (trace_new ArrangePhase);
	}

	case EPhaseType::NONE:
	{
		break;
	}

	default:
	{
		break;
	}
	}

	return nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

EErrorType EntrancePhase::OnInitialize()
{	
	InputController::I()->InsertInputMappingInfo("GotoIntro", VK_ESCAPE);
	InputController::I()->InsertInputMappingInfo("SelectUp", VK_UP);
	InputController::I()->InsertInputMappingInfo("SelectDown", VK_DOWN);
	InputController::I()->InsertInputMappingInfo("SelectLeft", VK_LEFT);
	InputController::I()->InsertInputMappingInfo("SelectRight", VK_RIGHT);
	InputController::I()->InsertInputMappingInfo("SelectMenu", VK_RETURN);

	return EErrorType::NONE;
}

EErrorType EntrancePhase::OnPostInitialize()
{
	ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	consoleSelector.setSelectorPos(2, 4);
	consoleSelector.setMinSelectorPos(2, 4);
	consoleSelector.setMaxSelectorPos(19, 6);

	return EErrorType();
}

EErrorType EntrancePhase::OnUpdate()
{
	if (InputController::I()->CheckInputState("GotoIntro", EInputMappingState::DOWN) == true)
	{
		SceneMgr::I()->CreateScene<IntroMenuScene>(ESceneType::NEXT);
	}

	if (InputController::I()->CheckInputState("SelectLeft", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosX(-17);
		DEBUG_LOG("SelectLeft ������!");
	}

	if (InputController::I()->CheckInputState("SelectRight", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosX(+17);
		DEBUG_LOG("SelectRight ������!");
	}

	if (InputController::I()->CheckInputState("SelectUp", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(-2);
		DEBUG_LOG("SelectUp ������!");
	}

	if (InputController::I()->CheckInputState("SelectDown", EInputMappingState::DOWN) == true)
	{
		ConsoleController::I()->AddSelectorPosY(+2);
		DEBUG_LOG("SelectDown ������!");
	}

	if (InputController::I()->CheckInputState("SelectMenu", EInputMappingState::DOWN) == true)
	{
		setCurrentPhaseType(EntrancePhaseHelper::ToPhaseType(ConsoleController::I()->GetCurrentConsoleSelectorPos()));

		PhaseBase* pNextPhase = EntrancePhaseHelper::CreateNextPhase(getCurrentPhaseType());
		if (pNextPhase == nullptr)
		{
			SceneMgr::I()->CreateScene<IntroMenuScene>(ESceneType::NEXT);
		}
		
		setNextPhase(pNextPhase);
		DEBUG_LOG("SelectMenu ������!");
	}

	return EErrorType::NONE;
}

EErrorType EntrancePhase::OnRender()
{
	Int32 drawPosY = -1;
	PRINTF(0, ++drawPosY, "����������������������������������������������������������������������");
	PRINTF(0, ++drawPosY, "�� ��ȭ ������ ���� �� ȯ���ؿ�~!  ��");
	PRINTF(0, ++drawPosY, "�� ���� �Ϸ� ���̳���?             ��");
	PRINTF(0, ++drawPosY, "����������������������������������������������������������������������");
	PRINTF(0, ++drawPosY, "��    ����        ��    �Ǹ�        ��");
	PRINTF(0, ++drawPosY, "����������������������������������������������������������������������");
	PRINTF(0, ++drawPosY, "��    ����        ��    ������      ��");
	PRINTF(0, ++drawPosY, "����������������������������������������������������������������������");

	ConsoleController::I()->DrawSelector();
	return EErrorType::NONE;
}

EErrorType EntrancePhase::OnFinalize()
{
	return EErrorType::NONE;
}
