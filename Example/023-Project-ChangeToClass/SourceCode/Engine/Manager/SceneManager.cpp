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

void SceneMgr::FlipCurrentScene()
{
	SAFE_SWAP_DELETE(m_pCurrentScene, m_pNextScene);
	DEBUG_LOG_CATEGORY(SceneMgr, "%s ������ %s ������ ��ȯ!",
		m_pCurrentScene->getNameTag().c_str(), m_pNextScene->getNameTag().c_str());
}

void SceneMgr::DeleteScene()
{
	SAFE_DELETE(m_pCurrentScene);
	SAFE_DELETE(m_pNextScene);
}