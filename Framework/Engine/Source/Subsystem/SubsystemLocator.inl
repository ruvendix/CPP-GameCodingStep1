// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 모든 서비스에 접근할 때 사용됩니다.
// 서비스 로케이터는 싱글톤으로 구현했습니다.
// ======================================================================================
template <typename TSubsystem>
inline void SubsystemLocator::RegisterSubsystem()
{
	static_assert(std::is_base_of_v<ISubsystem, TSubsystem>, "It't not subsystem!");

	if (FindSubsystem<TSubsystem>() != nullptr)
	{
		::OutputDebugString("이미 같은 계열의 서브시스템이 존재합니다!\n");
		return;
	}

	ISubsystem* pSubsystem = new TSubsystem;
	if (pSubsystem == nullptr)
	{
		::OutputDebugString("힙메모리 부족으로 서브시스템을 생성할 수 없습니다!\n");
		return;
	}

	const auto& ret = m_mapSubsystem.emplace(TSubsystem::Type(), pSubsystem);
	if (ret.second == false) // 삽입 실패인 경우
	{
		::OutputDebugString("서브시스템을 추가하지 못했습니다!\n");
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
		//::OutputDebugString("서브시스템을 찾을 수 없습니다!\n"); // 필요할 때만 사용
		return nullptr;
	}

	// 템플릿은 타입을 정확하게 알고 있으므로 static_cast로 성능을 향상시킵니다.
	// dynamic_cast는 RTTI에 의존하므로 캐스팅 오버헤드가 좀 있어요.
	TSubsystem* pSubsystem = DownCast<ISubsystem, TSubsystem>(iter->second);
	if (pSubsystem == nullptr)
	{
		::OutputDebugString("서브시스템을 캐스팅할 수 없습니다!\n");
		return nullptr;
	}

	return pSubsystem;
}

template <typename TSubsystem>
inline void SubsystemLocator::ExchangeSubsystem()
{
	static_assert(std::is_base_of_v<ISubsystem, TSubsystem>, "It't not subsystem!");

	// FindSubsystem()은 반환값을 사용할 때만 의미가 있으니 따로 찾아야 합니다.
	const auto& iter = m_mapSubsystem.find(TSubsystem::Type());
	if (iter->second == nullptr)
	{
		::OutputDebugString("교체할 서브시스템이 없습니다!\n");
		return;
	}

	iter->second->CleanUp();
	SAFE_DELETE(iter->second);

	TSubsystem* pSubsystem = new TSubsystem;
	if (pSubsystem == nullptr)
	{
		::OutputDebugString("힙메모리 부족으로 서브시스템을 생성할 수 없습니다!\n");
		return;
	}

	pSubsystem->SetUp();
	iter->second = pSubsystem;
}