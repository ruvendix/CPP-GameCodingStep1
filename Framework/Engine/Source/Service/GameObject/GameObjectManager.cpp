// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ������Ʈ�� �����մϴ�.
// �Ŵ����� ��ϵ� ���� ������Ʈ�� �ٷ� �� �ֽ��ϴ�.
// =====================================================================================
#include "EnginePCH.h"
#include "GameObjectManager.h"

#include "Service/ServiceInclusion.h"
#include "GameObject.h"

/*
	�Ŵ����� ���� ������Ʈ�� ����մϴ�.
*/
EReturnType GameObjectManager::AddGameObject(GameObject* pGameObj)
{
	CHECK_NULLPTR(pGameObj);
	m_mapGameObject.insert(std::make_pair(m_ID, pGameObj));
	++m_ID;

	if (m_ID == std::numeric_limits<Uint32>::max())
	{
		RX_ERRORTYPE(LogGameObjectManager, EErrorType::OUT_OF_GAMEOBJECT);
		return EReturnType::FAIL;
	}

	return EReturnType::SUCCESS;
}

/*
	�Ŵ����� ��ϵ� ��� ���� ������Ʈ�� ������ �����մϴ�.
*/
EReturnType GameObjectManager::UpdateAllGameObject()
{
	for (auto& iter : m_mapGameObject)
	{
		if (iter.second == nullptr)
		{
			continue;
		}

		iter.second->Update();
	}

	return EReturnType::SUCCESS;
}

/*
	�Ŵ����� ��ϵ� ��� ���� ������Ʈ�� �׸��ϴ�.
*/
EReturnType GameObjectManager::RenderAllGameObject()
{
	for (auto& iter : m_mapGameObject)
	{
		if (iter.second == nullptr)
		{
			continue;
		}

		iter.second->Render();
	}

	return EReturnType::SUCCESS;
}
