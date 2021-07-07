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
#pragma once

#include "Common/CommonBase.h"
#include "Subsystem/ISubsytem.h"

// ���� ����
class Actor;

class IActorManager : public ISubsystem
{
	GENERATE_SUBSYSTEM_TYPE(ESubsystemType::ACTOR_MANAGER);

public:
	IActorManager() = default;
	virtual ~IActorManager();

	template <typename TActor>
	TActor* CreateActor();

	void AddActor(Actor* pActor); // �̰ɷ� �߰��� ���͸� ����!
	void Update();
	
	UINT32 GetActorCount() const { return m_vecActor.size(); }

private:
	std::vector<Actor*> m_vecActor;
};