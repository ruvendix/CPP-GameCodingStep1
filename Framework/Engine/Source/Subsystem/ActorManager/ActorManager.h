// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ���� �� ���͸� �����մϴ�.
// =====================================================================================
#pragma once

#include "Base/IActorManager.h"

class ActorManager final : public IActorManager
{
	ONLY_SUBSYSTEM(ActorManager);

public:
	virtual void StartUp() override;
	virtual void CleanUp() override;

	virtual void AddActor(Actor* pActor) override; // �̰ɷ� �߰��� ���͸� ����!
	virtual void Update() override;

private:
	std::vector<Actor*> m_vecActor;
};