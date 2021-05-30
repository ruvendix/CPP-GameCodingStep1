// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 게임 오브젝트를 관리합니다.
// 매니저에 등록된 게임 오브젝트만 다룰 수 있습니다.
// =====================================================================================
#include "EnginePCH.h"
#include "GameObjectManager.h"

#include "Subsystem/SubsystemInclusion.h"
#include "GameObject/GameObject.h"

/*
	매니저에 게임 오브젝트를 등록합니다.
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
	매니저에 등록된 모든 게임 오브젝트의 내용을 갱신합니다.
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
	매니저에 등록된 모든 게임 오브젝트를 그립니다.
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
