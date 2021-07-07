// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������Ʈ �������̽��Դϴ�.
// ����Լ��� �����Ǿ��ְ� ��������� ���� �ִ� �߻� Ŭ�����Դϴ�.
// C++������ �������̽��� �߻� Ŭ������ ������ �����Ƿ� �� �� ���λ� I�� ����մϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "Common/CommonMacro.h"

#include "ComponentMacro.h"
#include "ComponentEnum.h"

class Actor;

class IComponent
{
public:
	IComponent(Actor* pActor);
	virtual ~IComponent() = default;

	virtual void SetUp() PURE_FUNC;
	virtual void Update() PURE_FUNC;

	Actor* GetActor() const { return m_pActor; }

private:
	Actor* m_pActor = nullptr;
};