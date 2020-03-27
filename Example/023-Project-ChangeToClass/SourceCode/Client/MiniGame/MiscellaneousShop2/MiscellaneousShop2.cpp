// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �پ��� �������� ���� �� �Ǹ��ϴ� ��ȭ����2�Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "MiscellaneousShop2.h"

#include "Controller\InputController.h"
#include "Controller\ConsoleController.h"
#include "Manager\TriggerTimerManager.h"
#include "Phase\EntrancePhase.h"

EErrorType MiscellanouseShop2::OnInitialize()
{
	SAFE_DELETE(m_pCurrentPhase);
	m_pCurrentPhase = trace_new EntrancePhase;

	if (m_pCurrentPhase->OnPostInitialize() == EErrorType::INIT_FAILED)
	{
		return EErrorType::INIT_FAILED;
	}

	if (m_pCurrentPhase->OnInitialize() == EErrorType::INIT_FAILED)
	{
		return EErrorType::INIT_FAILED;
	}

	return EErrorType::NONE;
}

EErrorType MiscellanouseShop2::OnInput()
{
	if (m_pCurrentPhase->OnInput() == EErrorType::INPUT_FAILED)
	{
		return EErrorType::INPUT_FAILED;
	}

	return EErrorType::NONE;
}

EErrorType MiscellanouseShop2::OnUpdate()
{
	if (m_pCurrentPhase->OnUpdate() == EErrorType::UPDATE_FAILED)
	{
		return EErrorType::UPDATE_FAILED;
	}

	if (m_pCurrentPhase->HasNextPhase())
	{
		TriggerTimerMgr::I()->DeleteTriggerTimer("RenderString");

		if (m_pCurrentPhase->OnFinalize() == EErrorType::FINAL_FAILED)
		{
			return EErrorType::FINAL_FAILED;
		}
		
		PhaseBase* pNextPhase = m_pCurrentPhase->getNextPhase();
		CHECK_NULLPTR(pNextPhase);

		if (pNextPhase->OnInitialize() == EErrorType::INIT_FAILED)
		{
			return EErrorType::INIT_FAILED;
		}

		if (m_pCurrentPhase->getLevel() < pNextPhase->getLevel())
		{
			ConsoleController::I()->PushBackupConsoleSelector();
			pNextPhase->OnPostInitialize();
		}
		else if (ConsoleController::I()->IsEmptySelector() == false)
		{
			ConsoleController::I()->RestoreConsoleSelector();
		}
		
		SAFE_SWAP_DELETE(m_pCurrentPhase, pNextPhase);
	}

	return EErrorType::NONE;
}

EErrorType MiscellanouseShop2::OnRender()
{
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::WHITE);

	if (m_pCurrentPhase->OnRender() == EErrorType::RENDER_FAILED)
	{
		return EErrorType::RENDER_FAILED;
	}

	return EErrorType::NONE;
}

EErrorType MiscellanouseShop2::OnFinalize()
{
	if (m_pCurrentPhase->OnFinalize() == EErrorType::FINAL_FAILED)
	{
		return EErrorType::FINAL_FAILED;
	}

	SAFE_DELETE(m_pCurrentPhase);

	return EErrorType::NONE;
}
