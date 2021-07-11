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

	if (CheckDuplicatedSubsystem<TSubsystem>() == true)
	{
		RX_ERROR2(LogSubsystemLocator, EErrorCode::DUPLICATED_SUBSYSTEM);
		return;
	}

	ISubsystem* pSubsystem = new TSubsystem;
	if (pSubsystem == nullptr)
	{
		RX_ERROR2(LogSubsystemLocator, EErrorCode::OUT_OF_HEAP_MEMORY);
		return;
	}

	const auto& ret = m_mapSubsystem.emplace(TSubsystem::Type(), pSubsystem);
	if (ret.second == false) // ���� ������ ���
	{
		RX_ERROR2(LogSubsystemLocator, EErrorCode::REGISTER_SUBSYSTEM_FAIL);
		SAFE_DELETE(pSubsystem);
		return;
	}

	pSubsystem->SetUp();
}

template<typename TSubsystem>
inline bool SubsystemLocator::CheckDuplicatedSubsystem() const
{
	static_assert(std::is_base_of_v<ISubsystem, TSubsystem>, "It't not subsystem!");

	const auto& iter = m_mapSubsystem.find(TSubsystem::Type());
	if ((iter == m_mapSubsystem.cend()) ||
		(iter->second == nullptr))
	{
		return false;
	}

	return true;
}

template <typename TSubsystem, typename TNullSubsystem>
inline TSubsystem* SubsystemLocator::FindSubsystem() const
{
	static_assert(std::is_base_of_v<ISubsystem, TSubsystem>, "It't not subsystem!");
	
	const auto& iter = m_mapSubsystem.find(TSubsystem::Type());
	if ((iter == m_mapSubsystem.cend()) ||
		(iter->second == nullptr))
	{
		RX_TRACE2(LogSubsystemLocator, "��Ͽ� �����Ƿ� �μ���ý����� ����մϴ�.");
		static TNullSubsystem null;
		return &null;
	}

	// ���ø��� Ÿ���� ��Ȯ�ϰ� �˰� �����Ƿ� static_cast�� ������ ����ŵ�ϴ�.
	// dynamic_cast�� RTTI�� �����ϹǷ� ĳ���� ������尡 �� �־��.
	TSubsystem* pSubsystem = DownCast<ISubsystem, TSubsystem>(iter->second);
	if (pSubsystem == nullptr)
	{
		RX_TRACE2(LogSubsystemLocator, "��Ͽ� �����Ƿ� �μ���ý����� ����մϴ�.");
		static TNullSubsystem null;
		return &null;
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
		RX_ERROR2(LogSubsystemLocator, EErrorCode::NOT_EXIST_SUBSYSTEM);
		return;
	}

	iter->second->CleanUp();
	SAFE_DELETE(iter->second);

	TSubsystem* pSubsystem = new TSubsystem;
	if (pSubsystem == nullptr)
	{
		RX_ERROR2(LogSubsystemLocator, EErrorCode::OUT_OF_HEAP_MEMORY);
		return;
	}

	pSubsystem->SetUp();
	iter->second = pSubsystem;
}