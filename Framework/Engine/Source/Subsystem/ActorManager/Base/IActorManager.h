// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 액터 관리자의 인터페이스입니다.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "Subsystem/ISubsytem.h"

// 전방 선언
class Actor;

class IActorManager : public ISubsystem
{
	GENERATE_SUBSYSTEM(ESubsystemType::ACTOR_MANAGER);

public:
	IActorManager() = default;
	virtual ~IActorManager() = default;

	template <typename TActor>
	TActor* CreateActor();

	virtual void AddActor(Actor* pActor) PURE_FUNC; // 이걸로 추가된 액터만 관리!
	virtual void Update() PURE_FUNC;
};