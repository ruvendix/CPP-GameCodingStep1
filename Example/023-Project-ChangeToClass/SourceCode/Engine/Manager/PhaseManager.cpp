// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������ ���� �� ��ȯ ���� ó���ϰ� �����մϴ�.
// =====================================================================================

#include "PCH.h"
#include "PhaseManager.h"

#include "Manager\TriggerTimerManager.h"

DEFINE_LOG_CATEGORY(PhaseMgr);
DEFINE_PHOENIX_SINGLETON(PhaseMgr);

/*
���� ����� �ִٰ� �����ϹǷ� �������� ó���� �����ҰԿ�
*/
EErrorType PhaseMgr::Flip()
{
	DEBUG_LOG_CATEGORY(PhaseMgr, "(%s) ������� (%s) ������� ��ȯ!",
		m_spCurrentPhase->getNameTag().c_str(), m_spNextPhase->getNameTag().c_str());

	TriggerTimerMgr::I()->DeleteTriggerTimer("RenderString");

	if (m_spCurrentPhase->OnFinalize() == EErrorType::FINAL_FAIL)
	{
		return EErrorType::FINAL_FAIL;
	}

	// ����� ��ȯ�� ���� �������� ��ǥ�� �����ؾ� �ϴ��� Ȯ���ؾ� �ؿ�!
	if ( (m_spCurrentPhase->getLevel() >= m_spNextPhase->getLevel()) &&
		 (ConsoleController::I()->IsEmptySelector() == false) )
	{
		ConsoleController::I()->RestoreConsoleSelector();
		if (m_spNextPhase->OnPostInitialize() == EErrorType::INIT_FAIL)
		{
			return EErrorType::INIT_FAIL;
		}
	}

	// ���� �������� ������ �̵�
	m_spCurrentPhase = std::move(m_spNextPhase);

	return EErrorType::NOTHING;
}
