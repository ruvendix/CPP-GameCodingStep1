// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 컴포넌트를 가질 수 있는 기본 액터입니다.
// 기본 액터를 상속받아서 Update()를 구현할 수 있습니다.
// =====================================================================================
#include "EnginePCH.h"
#include "Actor.h"

Actor::Actor()
{
	m_vecComponent.reserve(DEFAULT_COMPONENT_COUNT);
}

Actor::Actor(const std::string& strName) : Actor()
{
	m_strName = strName;
}

void Actor::Update()
{

}