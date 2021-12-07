// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �⺻ ������ ���ø� �Լ����� �����Ǿ��ֽ��ϴ�.
// =====================================================================================

/*
	���Ϳ� ������Ʈ�� �߰��մϴ�.
	�̹� �߰��� ������Ʈ�� �ִٸ� ������ ó���մϴ�.
*/
template <typename TComponent>
bool Actor::AddComponent()
{
	// �̹� ���� �Ǵ� ���� �迭�� Component�� �ִ��� Ȯ�� (��Ÿ�� �ܰ迡�� ����)
	if (FindComponent<TComponent>(true) != nullptr)
	{
		return false;
	}

	// ������� ���� ���ο� Component�� �߰��ؾ� �� ��!
	ComponentPtr spComponent = std::make_shared<TComponent>(this); // �����ڴ� �ڱ� �ڽ����� ����!
	if (spComponent == nullptr)
	{
		return false;
	}

	spComponent->StartUp();
	m_vecComponent.push_back(spComponent);
	return true;
}

/*
	���Ϳ��� ������Ʈ�� �����մϴ�.
	���Ϳ� ���� ������Ʈ��� ������ ó���մϴ�.
*/
template <typename TComponent>
inline bool Actor::RemoveComponent()
{
	// �̹� ���� �Ǵ� ���� �迭�� Component�� �ִ��� Ȯ�� (��Ÿ�� �ܰ迡�� ����)
	TComponent* pComponent = FindComponent<TComponent>();
	if (pComponent == nullptr)
	{
		printf("TComponent�� ����!\n");
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
	printf("TComponent ���� �Ϸ�!\n");

	return true;
}

/*
	���Ϳ��� ������Ʈ�� ã���ݴϴ�.
	���Ϳ� ���� ������Ʈ��� ������ ó���մϴ�.
*/

template <typename TComponent>
inline TComponent* Actor::FindComponent(bool bCheckHiearachy)
{
	// ������ �ܰ迡�� ����
	static_assert(std::is_base_of_v<IComponent, TComponent>, "It's not component!");

	IComponent* pDestComponent = TComponent::StaticClass();
	pDestComponent->InitClassMetadata(); // bool ������ üũ�ϱ� �������� �׳� ��� �ʱ�ȭ

	for (ComponentPtr spComponent : m_vecComponent)
	{
		RClass* pSrcComponent = spComponent->GetClass(); // ĳ������ �ʿ�� ����
		IComponent* pComponentInstance = spComponent.get();

		if (bCheckHiearachy == true)
		{
			if (pSrcComponent->IsUpperClass(pDestComponent))
			{
				printf("Dest�� �θ� Component!\n");
				return static_cast<TComponent*>(pSrcComponent);
			}

			if (pDestComponent->IsUpperClass(pSrcComponent))
			{
				printf("Dest�� �ڽ� Component!\n");
				printf("���� static ���� ���!\n");
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