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

#include "Subsystem/SubsystemInclusion.h"
#include "GameObject/GameObject.h"

/*
	�Ŵ����� ���� ������Ʈ�� ����մϴ�.
*/
void GameObjectManager::AddGameObject(GameObject* pGameObj)
{
	CHECK_NULLPTR(pGameObj);
	m_mapGameObject.insert(std::make_pair(m_ID, pGameObj));
	++m_ID;

	if (m_ID == std::numeric_limits<Uint32>::max())
	{
		RX_ERROR(LogGameObjectManager, EErrorCode::OUT_OF_GAMEOBJECT);
	}
}

/*
	�Ŵ����� ��ϵ� ��� ���� ������Ʈ�� ������ �����մϴ�.
*/
void GameObjectManager::UpdateAllGameObject()
{
	for (auto& iter : m_mapGameObject)
	{
		if (iter.second == nullptr)
		{
			continue;
		}

		iter.second->Update();
	}
}

/*
	�Ŵ����� ��ϵ� ��� ���� ������Ʈ�� �׸��ϴ�.
*/
void GameObjectManager::RenderAllGameObject()
{
	for (auto& iter : m_mapGameObject)
	{
		if (iter.second == nullptr)
		{
			continue;
		}

		iter.second->Render();
	}
}
