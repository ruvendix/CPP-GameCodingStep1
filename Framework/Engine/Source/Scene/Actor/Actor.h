// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������Ʈ�� ���� �� �ִ� �⺻ �����Դϴ�.
// �⺻ ���͸� ��ӹ޾Ƽ� Update()�� ������ �� �ֽ��ϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "../Component/ComponentEnum.h"
#include "ActorMacro.h"

// ������Ʈ�� ���͸� ���ؼ��� ���ǹǷ� ����Ÿ���� �����մϴ�.
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