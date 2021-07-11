// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ������Ʈ�� �����մϴ�.
// �����ڿ� ��ϵ� ���� ������Ʈ�� �ٷ� �� �ֽ��ϴ�.
// =====================================================================================
#pragma once

#include "Base/IGameObjectManager.h"

// ���� ����
class GameObject;
class GameObjectManagerInside;

class GameObjectManager final : public IGameObjectManager
{
	ONLY_SUBSYSTEM_CTOR(GameObjectManager);

public:
	virtual void SetUp() OVERRIDE_EMPTY_FUNC;
	virtual void CleanUp() override;

	virtual void AddGameObject(GameObject* pGameObj) override;

	virtual void UpdateAllGameObject() override;
	virtual void RenderAllGameObject() override;

private:
	std::unique_ptr<GameObjectManagerInside> m_spInside = nullptr;
};