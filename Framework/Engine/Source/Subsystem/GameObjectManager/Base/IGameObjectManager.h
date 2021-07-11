// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ������Ʈ �������� �������̽��Դϴ�.
// =====================================================================================
#pragma once

#include "Subsystem/ISubsytem.h"

// ���� ����
class GameObject;

class IGameObjectManager : public ISubsystem
{
	GENERATE_SUBSYSTEM(ESubsystemType::GAME_OBJECT_MANAGER);

public:
	IGameObjectManager() = default;
	virtual ~IGameObjectManager() = default;

	virtual void AddGameObject(GameObject* pGameObj) PURE_FUNC;

	virtual void UpdateAllGameObject() PURE_FUNC;
	virtual void RenderAllGameObject() PURE_FUNC;
};