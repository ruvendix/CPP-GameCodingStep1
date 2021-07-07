// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 액터 관리자의 인터페이스입니다.
// 멤버함수가 구현되어있고 멤버변수도 갖고 있는 추상 클래스입니다.
// C++에서는 인터페이스와 추상 클래스의 구분이 없으므로 둘 다 접두사 I를 사용합니다.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "Subsystem/ISubsytem.h"

// 전방 선언
class Actor;

class IActorManager : public ISubsystem
{
	GENERATE_SUBSYSTEM_TYPE(ESubsystemType::ACTOR_MANAGER);

public:
	IActorManager() = default;
	virtual ~IActorManager();

	template <typename TActor>
	TActor* CreateActor();

	void AddActor(Actor* pActor); // 이걸로 추가된 액터만 관리!
	void Update();
	
	UINT32 GetActorCount() const { return m_vecActor.size(); }

private:
	std::vector<Actor*> m_vecActor;
};