// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 액터 생성 및 액터를 관리합니다.
// =====================================================================================
#include "EnginePCH.h"
#include "ActorManager.h"

#include "Scene/Actor/Base/Actor.h"

void ActorManager::SetUp()
{

}

void ActorManager::CleanUp()
{
	for (auto& iter : m_vecActor)
	{
		SAFE_DELETE(iter);
	}
}

void ActorManager::AddActor(Actor* pActor)
{
	m_vecActor.push_back(pActor);
}

void ActorManager::Update()
{
	for (auto& iter : m_vecActor)
	{
		iter->Update();
	}
}