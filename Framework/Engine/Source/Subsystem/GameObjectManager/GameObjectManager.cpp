// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 게임 오브젝트를 관리합니다.
// 관리자에 등록된 게임 오브젝트만 다룰 수 있습니다.
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
	관리자에 게임 오브젝트를 등록합니다.
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
	관리자에 등록된 모든 게임 오브젝트의 내용을 갱신합니다.
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
	관리자에 등록된 모든 게임 오브젝트를 그립니다.
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