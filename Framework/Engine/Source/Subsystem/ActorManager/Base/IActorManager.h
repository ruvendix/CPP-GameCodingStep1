// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �������� �������̽��Դϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "Subsystem/ISubsytem.h"

// ���� ����
class Actor;

class IActorManager : public ISubsystem
{
	GENERATE_SUBSYSTEM(ESubsystemType::ACTOR_MANAGER);

public:
	IActorManager() = default;
	virtual ~IActorManager() = default;

	template <typename TActor>
	TActor* CreateActor();

	virtual void AddActor(Actor* pActor) PURE_FUNC; // �̰ɷ� �߰��� ���͸� ����!
	virtual void Update() PURE_FUNC;
};