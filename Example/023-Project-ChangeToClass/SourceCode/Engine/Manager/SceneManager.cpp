// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �� ���� �� ��ȯ ���� ó�����ִ� �Ŵ����Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "SceneManager.h"

DEFINE_LOG_CATEGORY(SceneMgr);
DEFINE_SINGLETON(SceneMgr);

/*
���� ���� ���� ���� ��ȯ�մϴ�.
*/
void SceneMgr::FlipCurrentScene()
{
	const std::string& strPrevSceneName = m_pCurrentScene->getNameTag();
	SAFE_SWAP_DELETE(m_pCurrentScene, m_pNextScene);
	DEBUG_LOG_CATEGORY(SceneMgr, "(%s) ������ (%s) ������ ��ȯ!",
		strPrevSceneName.c_str(), m_pCurrentScene->getNameTag().c_str());
}

/*
��� ���� �����մϴ�.
*/
void SceneMgr::Finalize()
{
	SAFE_DELETE(m_pCurrentScene);
	SAFE_DELETE(m_pNextScene);
}