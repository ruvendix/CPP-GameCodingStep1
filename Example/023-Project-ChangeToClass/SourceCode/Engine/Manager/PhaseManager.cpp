// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 페이즈 생성 및 전환 등을 처리하고 관리합니다.
// =====================================================================================

#include "PCH.h"
#include "PhaseManager.h"

#include "Manager\TriggerTimerManager.h"

DEFINE_LOG_CATEGORY(PhaseMgr);
DEFINE_PHOENIX_SINGLETON(PhaseMgr);

/*
다음 페이즈가 있다고 가정하므로 널포인터 처리는 생략할게요
*/
EErrorType PhaseMgr::Flip()
{
	DEBUG_LOG_CATEGORY(PhaseMgr, "(%s) 페이즈에서 (%s) 페이즈로 전환!",
		m_spCurrentPhase->getNameTag().c_str(), m_spNextPhase->getNameTag().c_str());

	TriggerTimerMgr::I()->DeleteTriggerTimer("RenderString");

	if (m_spCurrentPhase->OnFinalize() == EErrorType::FINAL_FAIL)
	{
		return EErrorType::FINAL_FAIL;
	}

	// 페이즈를 전환할 때는 셀렉터의 좌표를 복원해야 하는지 확인해야 해요!
	if ( (m_spCurrentPhase->getLevel() >= m_spNextPhase->getLevel()) &&
		 (ConsoleController::I()->IsEmptySelector() == false) )
	{
		ConsoleController::I()->RestoreConsoleSelector();
		if (m_spNextPhase->OnPostInitialize() == EErrorType::INIT_FAIL)
		{
			return EErrorType::INIT_FAIL;
		}
	}

	// 다음 페이즈의 소유권 이동
	m_spCurrentPhase = std::move(m_spNextPhase);

	return EErrorType::NOTHING;
}
