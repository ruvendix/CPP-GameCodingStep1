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
#include "../../Component/Base/IComponent.h"

// ��ȣ ���� ����!
class IComponent;

// ������Ʈ�� ���͸� ���ؼ��� ���ǹǷ� ����Ÿ���� �����մϴ�.
using ComponentPtr = std::shared_ptr<IComponent>;

class Actor
{
public:
    static const UINT32 DEFAULT_COMPONENT_COUNT = 4;

    Actor();
    Actor(const std::string& strName);
    virtual ~Actor() = default;

    virtual void Update();

    template <typename TComponent>
    bool AddComponent();

    template <typename TComponent>
    bool RemoveComponent();

    template <typename TComponent>
    TComponent* FindComponent(bool bCheckHiearachy = false);

    const std::string& GetName() const { return m_strName; }
    void SetName(const std::string& strName) { m_strName = strName; }

private:
    std::string m_strName; // �������� �۾��� ���� ȣȯ�� �ִ� ��Ʈ���� ����ϴ� �� ��õ! (�𸮾󿡼��� TEXT())
    std::vector<ComponentPtr> m_vecComponent; // ���⿡ Component���� ����!
};