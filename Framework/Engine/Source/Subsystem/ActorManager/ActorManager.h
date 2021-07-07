// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ���� �� ���͸� �����մϴ�.
// =====================================================================================
#pragma once

#include "IActorManager.h"

class ActorManager final : public IActorManager
{
	ONLY_SUBSYSTEM(ActorManager);

	virtual void SetUp() override;
	virtual void CleanUp() override;
};