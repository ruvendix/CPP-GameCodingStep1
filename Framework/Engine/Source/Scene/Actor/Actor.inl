// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �⺻ ������ ���ø� �Լ����� �����Ǿ��ֽ��ϴ�.
// =====================================================================================

class IComponent;

/*
	���Ϳ� ������Ʈ�� �߰��մϴ�.
	�̹� �߰��� ������Ʈ�� �ִٸ� ������ ó���մϴ�.
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
	if (ret.second == false) // ���� ������ ���
	{
		RX_ERROR(EErrorCode::ADD_COMPONENT_FAIL, TComponent::Tag());
		return;
	}

	spComponent->SetUp();
}


/*
	���Ϳ��� ������Ʈ�� �����մϴ�.
	���Ϳ� ���� ������Ʈ��� ������ ó���մϴ�.
*/
template <typename TComponent>
inline void Actor::RemoveComponent()
{

}

/*
	���Ϳ��� ������Ʈ�� ã���ݴϴ�.
	���Ϳ� ���� ������Ʈ��� ������ ó���մϴ�.
*/
template <typename TComponent>
inline std::shared_ptr<TComponent> Actor::FindComponent()
{
	static_assert(std::is_base_of_v<IComponent, TComponent>, "It't not component!");

	const auto& iter = m_mapComponent.find(TComponent::Type());
	if ((iter == m_mapComponent.cend()) ||
		(iter->second == nullptr))
	{
		//::OutputDebugString("������Ʈ�� ã�� �� �����ϴ�!\n"); // �ʿ��� ���� ���
		return nullptr;
	}

	// ���ø��� Ÿ���� ��Ȯ�ϰ� �˰� �����Ƿ� static_cast�� ������ ����ŵ�ϴ�.
	// dynamic_cast�� RTTI�� �����ϹǷ� ĳ���� ������尡 �� �־��.
	std::shared_ptr<TComponent> spComponent = DownCastSmartPointer<IComponent, TComponent>(iter->second);
	if (spComponent == nullptr)
	{
		RX_ERROR(EErrorCode::CASTING_FAIL);
		return nullptr;
	}

	return spComponent;
}
