// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 액터 생성 및 액터를 관리합니다.
// =====================================================================================
#pragma once

#include "Base/IActorManager.h"

class ActorManager final : public IActorManager
{
	ONLY_SUBSYSTEM(ActorManager);

public:
	virtual void StartUp() override;
	virtual void CleanUp() override;

	virtual void AddActor(Actor* pActor) override; // 이걸로 추가된 액터만 관리!
	virtual void Update() override;

private:
	std::vector<Actor*> m_vecActor;
};