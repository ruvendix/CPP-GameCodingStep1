// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ���� �� ���͸� �����մϴ�.
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