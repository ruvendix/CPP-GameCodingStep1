// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ������Ʈ�� �����մϴ�.
// �Ŵ����� ��ϵ� ���� ������Ʈ�� �ٷ� �� �ֽ��ϴ�.
// =====================================================================================
#pragma once

#include "IGameObjectManager.h"

class GameObject;

class GameObjectManager : public IGameObjectManager
{
public:
	GameObjectManager() = default;
	virtual ~GameObjectManager() = default;

	virtual void SetUp() override {  }
	virtual void CleanUp() override {  }

	virtual void AddGameObject(GameObject* pGameObj) override;

	virtual void UpdateAllGameObject() override;
	virtual void RenderAllGameObject() override;

private:
	Uint32 m_ID = 0;
	std::unordered_map<Uint32, GameObject*> m_mapGameObject;
};