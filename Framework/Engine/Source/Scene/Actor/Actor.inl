// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 기본 액터의 템플릿 함수들이 구현되어있습니다.
// =====================================================================================

class IComponent;

/*
	액터에 컴포넌트를 추가합니다.
	이미 추가된 컴포넌트가 있다면 에러로 처리합니다.
*/
template <typename TComponent>
inline void Actor::AddComponent()
{
	static_assert(std::is_base_of_v<IComponent, TComponent>, "It't not component!");

	if (FindComponent<TComponent>() != nullptr)
	{
		RX_ERROR(EErrorCode::DUPLICATED_COMPONENT, TComponent::Tag());
		return;
	}

	ComponentPtr spComponent = std::make_shared<TComponent>(this);
	if (spComponent == nullptr)
	{
		RX_ERROR(EErrorCode::OUT_OF_HEAP_MEMORY);
		return;
	}

	const auto& ret = m_mapComponent.emplace(TComponent::Type(), spComponent);
	if (ret.second == false) // 삽입 실패인 경우
	{
		RX_ERROR(EErrorCode::ADD_COMPONENT_FAIL, TComponent::Tag());
		return;
	}

	spComponent->SetUp();
}


/*
	액터에서 컴포넌트를 제거합니다.
	액터에 없는 컴포넌트라면 에러로 처리합니다.
*/
template <typename TComponent>
inline void Actor::RemoveComponent()
{

}

/*
	액터에서 컴포넌트를 찾아줍니다.
	액터에 없는 컴포넌트라면 에러로 처리합니다.
*/
template <typename TComponent>
inline std::shared_ptr<TComponent> Actor::FindComponent()
{
	static_assert(std::is_base_of_v<IComponent, TComponent>, "It't not component!");

	const auto& iter = m_mapComponent.find(TComponent::Type());
	if ((iter == m_mapComponent.cend()) ||
		(iter->second == nullptr))
	{
		//::OutputDebugString("컴포넌트를 찾을 수 없습니다!\n"); // 필요할 때만 사용
		return nullptr;
	}

	// 템플릿은 타입을 정확하게 알고 있으므로 static_cast로 성능을 향상시킵니다.
	// dynamic_cast는 RTTI에 의존하므로 캐스팅 오버헤드가 좀 있어요.
	std::shared_ptr<TComponent> spComponent = DownCastSmartPointer<IComponent, TComponent>(iter->second);
	if (spComponent == nullptr)
	{
		RX_ERROR(EErrorCode::CASTING_FAIL);
		return nullptr;
	}

	return spComponent;
}
