// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 씬 생성 및 전환 등을 처리하고 관리합니다.
// =====================================================================================

#include "PCH.h"
#include "SceneManager.h"

#include "Manager\TriggerTimerManager.h"

DEFINE_LOG_CATEGORY(SceneMgr);
DEFINE_PHOENIX_SINGLETON(SceneMgr);

/*
현재 씬과 다음 씬을 전환합니다.
*/
EErrorType SceneMgr::Flip()
{
	DEBUG_LOG_CATEGORY(SceneMgr, "(%s) 씬에서 (%s) 씬으로 전환!",
		m_spCurrentScene->getNameTag().c_str(), m_spNextScene->getNameTag().c_str());

	TriggerTimerMgr::I()->DeleteTriggerTimer("RenderString");

	if (m_spCurrentScene->OnFinalize() == EErrorType::FINAL_FAIL)
	{
		return EErrorType::FINAL_FAIL;
	}

	// 다음 페이즈의 소유권 이동
	m_spCurrentScene = std::move(m_spNextScene);

	return EErrorType::NOTHING;
}