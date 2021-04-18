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

#include "IGameObjectManger.h"

class GameObjectManager : public IGameObjectManager
{
public:
	GameObjectManager() = default;
	virtual ~GameObjectManager() = default;

	virtual EReturnType SetUp() override { return EReturnType::SUCCESS; }
	virtual EReturnType CleanUp() override { return EReturnType::SUCCESS; }

	virtual EReturnType AddGameObject(GameObject* pGameObj) override;

	virtual EReturnType UpdateAllGameObject() override;
	virtual EReturnType RenderAllGameObject() override;

private:
	Uint32 m_ID = 0;
	std::unordered_map<Uint32, GameObject*> m_mapGameObject;
};