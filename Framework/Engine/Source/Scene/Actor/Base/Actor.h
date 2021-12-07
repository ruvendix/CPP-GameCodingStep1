// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 컴포넌트를 가질 수 있는 기본 액터입니다.
// 기본 액터를 상속받아서 Update()를 구현할 수 있습니다.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "../../Component/Base/IComponent.h"

// 상호 참조 관계!
class IComponent;

// 컴포넌트는 액터를 통해서만 사용되므로 전역타입을 선언합니다.
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
    std::string m_strName; // 정식으로 작업할 때는 호환성 있는 스트링을 사용하는 걸 추천! (언리얼에서는 TEXT())
    std::vector<ComponentPtr> m_vecComponent; // 여기에 Component들을 모음!
};