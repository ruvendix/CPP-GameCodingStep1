// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ����� ���� ���� ������Ʈ �������Դϴ�.
// ���� ������Ʈ �����ڰ� �ʱ�ȭ���� �ʾ��� �� ���˴ϴ�.
// FIND_SUBSYSTEM() ��ũ�θ� ���ؼ��� ���˴ϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "IGameObjectManager.h"

class IGameObjectManagerNull : public IGameObjectManager
{
public:
	virtual void SetUp() OVERRIDE_EMPTY_FUNC;
	virtual void CleanUp() OVERRIDE_EMPTY_FUNC;

	virtual void AddGameObject(GameObject* pGameObj) OVERRIDE_EMPTY_FUNC;
	virtual void UpdateAllGameObject() OVERRIDE_EMPTY_FUNC;
	virtual void RenderAllGameObject() OVERRIDE_EMPTY_FUNC;
};