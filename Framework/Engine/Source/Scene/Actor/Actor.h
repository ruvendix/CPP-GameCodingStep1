// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 컴포넌트를 가질 수 있는 기본 액터입니다.
// 기본 액터를 상속받아서 Update()를 구현할 수 있습니다.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "../Component/ComponentEnum.h"
#include "ActorMacro.h"

// 컴포넌트는 액터를 통해서만 사용되므로 전역타입을 선언합니다.
using ComponentPtr = std::shared_ptr<class IComponent>;

class Actor
{
	ONLY_ACTOR_MANAGER(Actor);

public:
	template <typename TComponent>
	void AddComponent();

	template <typename TComponent>
	void RemoveComponent();

	template <typename TComponent>
	std::shared_ptr<TComponent> FindComponent();

	void Update();

protected:
	virtual void UpdateActor();

private:
	void UpdateComponent();

	std::unordered_map<EComponentType, ComponentPtr> m_mapComponent;
};