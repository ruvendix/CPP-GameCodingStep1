// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� ���񽺿� ������ �� ���˴ϴ�.
// ���� �������ʹ� �̱������� �����߽��ϴ�.
// ======================================================================================
template <typename TSubsystem>
inline void SubsystemLocator::RegisterSubsystem()
{
	static_assert(std::is_base_of_v<ISubsystem, TSubsystem>, "It't not subsystem!");

	if (FindSubsystem<TSubsystem>() != nullptr)
	{
		::OutputDebugString("�̹� ���� �迭�� ����ý����� �����մϴ�!\n");
		return;
	}

	ISubsystem* pSubsystem = new TSubsystem;
	if (pSubsystem == nullptr)
	{
		::OutputDebugString("���޸� �������� ����ý����� ������ �� �����ϴ�!\n");
		return;
	}

	const auto& ret = m_mapSubsystem.emplace(TSubsystem::Type(), pSubsystem);
	if (ret.second == false) // ���� ������ ���
	{
		::OutputDebugString("����ý����� �߰����� ���߽��ϴ�!\n");
		SAFE_DELETE(pSubsystem);
		return;
	}

	pSubsystem->SetUp();
}

template <typename TSubsystem>
inline TSubsystem* SubsystemLocator::FindSubsystem()
{
	static_assert(std::is_base_of_v<ISubsystem, TSubsystem>, "It't not subsystem!");

	const auto& iter = m_mapSubsystem.find(TSubsystem::Type());
	if ((iter == m_mapSubsystem.cend()) ||
		(iter->second == nullptr))
	{
		//::OutputDebugString("����ý����� ã�� �� �����ϴ�!\n"); // �ʿ��� ���� ���
		return nullptr;
	}

	// ���ø��� Ÿ���� ��Ȯ�ϰ� �˰� �����Ƿ� static_cast�� ������ ����ŵ�ϴ�.
	// dynamic_cast�� RTTI�� �����ϹǷ� ĳ���� ������尡 �� �־��.
	TSubsystem* pSubsystem = DownCast<ISubsystem, TSubsystem>(iter->second);
	if (pSubsystem == nullptr)
	{
		::OutputDebugString("����ý����� ĳ������ �� �����ϴ�!\n");
		return nullptr;
	}

	return pSubsystem;
}

template <typename TSubsystem>
inline void SubsystemLocator::ExchangeSubsystem()
{
	static_assert(std::is_base_of_v<ISubsystem, TSubsystem>, "It't not subsystem!");

	// FindSubsystem()�� ��ȯ���� ����� ���� �ǹ̰� ������ ���� ã�ƾ� �մϴ�.
	const auto& iter = m_mapSubsystem.find(TSubsystem::Type());
	if (iter->second == nullptr)
	{
		::OutputDebugString("��ü�� ����ý����� �����ϴ�!\n");
		return;
	}

	iter->second->CleanUp();
	SAFE_DELETE(iter->second);

	TSubsystem* pSubsystem = new TSubsystem;
	if (pSubsystem == nullptr)
	{
		::OutputDebugString("���޸� �������� ����ý����� ������ �� �����ϴ�!\n");
		return;
	}

	pSubsystem->SetUp();
	iter->second = pSubsystem;
}