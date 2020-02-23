// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 씬 생성 및 전환 등을 처리해주는 매니저입니다.
// =====================================================================================

#include "PCH.h"
#include "SceneManager.h"

DEFINE_LOG_CATEGORY(SceneMgr);
DEFINE_SINGLETON(SceneMgr);

/*
현재 씬과 다음 씬을 전환합니다.
*/
void SceneMgr::FlipCurrentScene()
{
	const std::string& strPrevSceneName = m_pCurrentScene->getNameTag();
	SAFE_SWAP_DELETE(m_pCurrentScene, m_pNextScene);
	DEBUG_LOG_CATEGORY(SceneMgr, "(%s) 씬에서 (%s) 씬으로 전환!",
		strPrevSceneName.c_str(), m_pCurrentScene->getNameTag().c_str());
}

/*
모든 씬을 제거합니다.
*/
void SceneMgr::Finalize()
{
	SAFE_DELETE(m_pCurrentScene);
	SAFE_DELETE(m_pNextScene);
}