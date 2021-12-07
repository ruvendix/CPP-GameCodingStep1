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

#include "Core/RClass/RClass.h"

// ��ȣ ���� ����!
class Actor;

class IComponent : public RClass
{
    GENERATE_HIERARCHY(IComponent, RClass);

public:
    IComponent() = default;
    IComponent(Actor* pOwner);
    virtual ~IComponent() = default;

    Actor* GetOwner() { return m_pOwner; }
    const Actor* GetOwner() const { return m_pOwner; }

private:
    Actor* m_pOwner = nullptr;
};