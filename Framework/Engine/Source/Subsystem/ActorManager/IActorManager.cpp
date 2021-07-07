// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �������� �������̽��Դϴ�.
// ����Լ��� �����Ǿ��ְ� ��������� ���� �ִ� �߻� Ŭ�����Դϴ�.
// C++������ �������̽��� �߻� Ŭ������ ������ �����Ƿ� �� �� ���λ� I�� ����մϴ�.
// =====================================================================================
#include "EnginePCH.h"
#include "IActorManager.h"

#include "Scene/Actor/Actor.h"

IActorManager::~IActorManager()
{
	for (auto& iter : m_vecActor)
	{
		SAFE_DELETE(iter);
	}
}

void IActorManager::AddActor(Actor* pActor)
{
	m_vecActor.push_back(pActor);
}

void IActorManager::Update()
{
	for (auto& iter : m_vecActor)
	{
		iter->Update();
	}
}