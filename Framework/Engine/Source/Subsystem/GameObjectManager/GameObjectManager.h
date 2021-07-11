// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 게임 오브젝트를 관리합니다.
// 관리자에 등록된 게임 오브젝트만 다룰 수 있습니다.
// =====================================================================================
#pragma once

#include "Base/IGameObjectManager.h"

// 전방 선언
class GameObject;
class GameObjectManagerInside;

class GameObjectManager final : public IGameObjectManager
{
	ONLY_SUBSYSTEM_CTOR(GameObjectManager);

public:
	virtual void SetUp() OVERRIDE_EMPTY_FUNC;
	virtual void CleanUp() override;

	virtual void AddGameObject(GameObject* pGameObj) override;

	virtual void UpdateAllGameObject() override;
	virtual void RenderAllGameObject() override;

private:
	std::unique_ptr<GameObjectManagerInside> m_spInside = nullptr;
};