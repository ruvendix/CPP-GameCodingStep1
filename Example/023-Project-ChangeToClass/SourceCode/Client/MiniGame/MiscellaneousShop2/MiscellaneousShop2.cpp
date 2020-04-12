// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 다양한 아이템을 구매 및 판매하는 잡화상점2입니다.
// =====================================================================================

#include "PCH.h"
#include "MiscellaneousShop2.h"

#include "Controller\InputController.h"
#include "Controller\ConsoleController.h"
#include "Manager\TriggerTimerManager.h"
#include "Manager\PhaseManager.h"
#include "Phase\EntrancePhase.h"

EErrorType MiscellaneousShop2::OnInitialize()
{
	PhaseMgr::I()->CreatePhase<EntrancePhase>(ECreateType::CURRENT, 0);
	return EErrorType::NOTHING;
}

EErrorType MiscellaneousShop2::OnInput()
{
	if (PhaseMgr::I()->getCurrentPhase()->OnInput() == EErrorType::INPUT_FAIL)
	{
		return EErrorType::INPUT_FAIL;
	}

	return EErrorType::NOTHING;
}

EErrorType MiscellaneousShop2::OnUpdate()
{
	if (PhaseMgr::I()->getCurrentPhase()->OnUpdate() == EErrorType::UPDATE_FAIL)
	{
		return EErrorType::UPDATE_FAIL;
	}

	if (PhaseMgr::I()->IsGotoNextPhase())
	{
		PhaseMgr::I()->Flip();
	}

	return EErrorType::NOTHING;
}

EErrorType MiscellaneousShop2::OnRender()
{
	//ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::WHITE);

	if (PhaseMgr::I()->getCurrentPhase()->OnRender() == EErrorType::RENDER_FAIL)
	{
		return EErrorType::RENDER_FAIL;
	}

	return EErrorType::NOTHING;
}

EErrorType MiscellaneousShop2::OnFinalize()
{
	if (PhaseMgr::I()->getCurrentPhase()->OnFinalize() == EErrorType::FINAL_FAIL)
	{
		return EErrorType::FINAL_FAIL;
	}

	PhaseMgr::I()->Reset();
	return EErrorType::NOTHING;
}
