// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 게임 오브젝트 매니저의 인터페이스입니다.
// =====================================================================================
#pragma once

#include "Common/CommonInterface.h"

// 전방 선언
class GameObject;

class IGameObjectManager : public ISubsystem
{
	GENERATE_SUBSYSTEM_TYPE(ESubsystemType::GAME_OBJECT_MANAGER);

public:
	IGameObjectManager() = default;
	virtual ~IGameObjectManager() = default;

	virtual void AddGameObject(GameObject* pGameObj) PURE_FUNC;

	virtual void UpdateAllGameObject() PURE_FUNC;
	virtual void RenderAllGameObject() PURE_FUNC;
};