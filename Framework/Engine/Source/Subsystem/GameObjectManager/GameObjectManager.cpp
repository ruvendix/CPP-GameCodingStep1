// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ������Ʈ�� �����մϴ�.
// �����ڿ� ��ϵ� ���� ������Ʈ�� �ٷ� �� �ֽ��ϴ�.
// =====================================================================================
#include "EnginePCH.h"
#include "GameObjectManager.h"

#include "Subsystem/SubsystemInclusion.h"
#include "Scene/GameObject/GameObject.h"

class GameObjectManagerInside final
{
public:
	GameObjectManagerInside() = default;
	~GameObjectManagerInside() = default;

	void AddGameObject(GameObject* pGameObj);
	void UpdateAllGameObject();
	void RenderAllGameObject();
	void CleanUp();

private:
	Uint32 m_objectIdx = 0;
	std::unordered_map<Uint32, GameObject*> m_mapGameObject;
};

void GameObjectManagerInside::AddGameObject(GameObject* pGameObject)
{
	CHECK_NULLPTR(pGameObject);
	m_mapGameObject.insert(std::make_pair(m_objectIdx, pGameObject));
	++m_objectIdx;

	if (m_objectIdx == std::numeric_limits<Uint32>::max())
	{
		RX_ERROR2(LogGameObjectManager, EErrorCode::OUT_OF_GAMEOBJECT);
	}
}

/*
	�����ڿ� ���� ������Ʈ�� ����մϴ�.
*/
void GameObjectManagerInside::UpdateAllGameObject()
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
	�����ڿ� ��ϵ� ��� ���� ������Ʈ�� ������ �����մϴ�.
*/
void GameObjectManagerInside::RenderAllGameObject()
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

/*
	�����ڿ� ��ϵ� ��� ���� ������Ʈ�� �׸��ϴ�.
*/
void GameObjectManagerInside::CleanUp()
{
	for (auto& iter : m_mapGameObject)
	{
		SAFE_DELETE(iter.second);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObjectManager::GameObjectManager()
{
	m_spInside = std::make_unique<GameObjectManagerInside>();
}

void GameObjectManager::CleanUp()
{
	m_spInside->CleanUp();
}

void GameObjectManager::AddGameObject(GameObject* pGameObj)
{
	m_spInside->AddGameObject(pGameObj);
}

void GameObjectManager::UpdateAllGameObject()
{
	m_spInside->UpdateAllGameObject();
}

void GameObjectManager::RenderAllGameObject()
{
	m_spInside->RenderAllGameObject();
}