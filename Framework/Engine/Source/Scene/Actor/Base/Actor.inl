// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 기본 액터의 템플릿 함수들이 구현되어있습니다.
// =====================================================================================

/*
	액터에 컴포넌트를 추가합니다.
	이미 추가된 컴포넌트가 있다면 에러로 처리합니다.
*/
template <typename TComponent>
bool Actor::AddComponent()
{
	// 이미 같은 또는 같은 계열의 Component가 있는지 확인 (런타임 단계에서 막음)
	if (FindComponent<TComponent>(true) != nullptr)
	{
		return false;
	}

	// 여기까지 오면 새로운 Component를 추가해야 할 때!
	ComponentPtr spComponent = std::make_shared<TComponent>(this); // 소유자는 자기 자신으로 설정!
	if (spComponent == nullptr)
	{
		return false;
	}

	spComponent->StartUp();
	m_vecComponent.push_back(spComponent);
	return true;
}

/*
	액터에서 컴포넌트를 제거합니다.
	액터에 없는 컴포넌트라면 에러로 처리합니다.
*/
template <typename TComponent>
inline bool Actor::RemoveComponent()
{
	// 이미 같은 또는 같은 계열의 Component가 있는지 확인 (런타임 단계에서 막음)
	TComponent* pComponent = FindComponent<TComponent>();
	if (pComponent == nullptr)
	{
		printf("TComponent가 없음!\n");
		return false;
	}

	auto foundIter = std::remove_if(m_vecComponent.begin(), m_vecComponent.end(),
		[pComponent](ComponentPtr spComponent)
		{
			return (pComponent == spComponent.get());
		});

	if (foundIter == m_vecComponent.cend())
	{
		return false;
	}

	m_vecComponent.erase(foundIter);
	printf("TComponent 제거 완료!\n");

	return true;
}

/*
	액터에서 컴포넌트를 찾아줍니다.
	액터에 없는 컴포넌트라면 에러로 처리합니다.
*/

template <typename TComponent>
inline TComponent* Actor::FindComponent(bool bCheckHiearachy)
{
	// 컴파일 단계에서 막기
	static_assert(std::is_base_of_v<IComponent, TComponent>, "It's not component!");

	IComponent* pDestComponent = TComponent::StaticClass();
	pDestComponent->InitClassMetadata(); // bool 변수로 체크하기 귀찮으니 그냥 계속 초기화

	for (ComponentPtr spComponent : m_vecComponent)
	{
		RClass* pSrcComponent = spComponent->GetClass(); // 캐스팅할 필요는 없음
		IComponent* pComponentInstance = spComponent.get();

		if (bCheckHiearachy == true)
		{
			if (pSrcComponent->IsUpperClass(pDestComponent))
			{
				printf("Dest는 부모 Component!\n");
				return static_cast<TComponent*>(pSrcComponent);
			}

			if (pDestComponent->IsUpperClass(pSrcComponent))
			{
				printf("Dest는 자식 Component!\n");
				printf("따라서 static 정보 사용!\n");
				return TComponent::StaticClass();
			}
		}

		if (pSrcComponent == pDestComponent)
		{
			return static_cast<TComponent*>(pComponentInstance);
		}
	}

	return nullptr;
}