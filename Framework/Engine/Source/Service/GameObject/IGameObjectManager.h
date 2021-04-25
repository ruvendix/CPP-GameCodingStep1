// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ������Ʈ �Ŵ����� �������̽��Դϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonInterface.h"

class GameObject;

class IGameObjectManager : public IService
{
public:
	IGameObjectManager() = default;
	virtual ~IGameObjectManager() = default;

	virtual EReturnType SetUp() override { return EReturnType::SUCCESS; }
	virtual EReturnType CleanUp() override { return EReturnType::SUCCESS; }

	virtual EReturnType AddGameObject(GameObject* pGameObj) = 0;

	virtual EReturnType UpdateAllGameObject() = 0;
	virtual EReturnType RenderAllGameObject() = 0;
};