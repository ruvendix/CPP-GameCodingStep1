// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �� ���� �� ��ȯ ���� ó���ϰ� �����մϴ�.
// =====================================================================================

#include "PCH.h"
#include "SceneManager.h"

#include "Manager\TriggerTimerManager.h"

DEFINE_LOG_CATEGORY(SceneMgr);
DEFINE_PHOENIX_SINGLETON(SceneMgr);

/*
���� ���� ���� ���� ��ȯ�մϴ�.
*/
EErrorType SceneMgr::Flip()
{
	DEBUG_LOG_CATEGORY(SceneMgr, "(%s) ������ (%s) ������ ��ȯ!",
		m_spCurrentScene->getNameTag().c_str(), m_spNextScene->getNameTag().c_str());

	TriggerTimerMgr::I()->DeleteTriggerTimer("RenderString");

	if (m_spCurrentScene->OnFinalize() == EErrorType::FINAL_FAIL)
	{
		return EErrorType::FINAL_FAIL;
	}

	// ���� �������� ������ �̵�
	m_spCurrentScene = std::move(m_spNextScene);

	return EErrorType::NOTHING;
}