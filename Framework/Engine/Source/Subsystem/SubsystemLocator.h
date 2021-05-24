// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 모든 서비스에 접근할 때 사용됩니다.
// 서비스 로케이터는 싱글톤으로 구현했습니다.
// =====================================================================================
#pragma once

#include "Common/CommonMacro.h"
#include "SubsystemEnum.h"

// 전방 선언
class ISubsystem;

// 서비스 로케이터 패턴을 활용했습니다.
class SubsystemLocator final
{
	GENERATE_LOCAL_SINGLETON(SubsystemLocator);

public:
	// 서브시스템은 추가하면 제거할 필요가 없습니다.
	template <typename TSubsystem>
	void AddSubsystem();

	template <typename TSubsystem>
	TSubsystem* FindSubsystem();

	void SetUp();
	void CleanUp();

private:
	std::unordered_map<ESubsystemType, ISubsystem*> m_mapSubsystem;
};

template<typename TSubsystem>
inline void SubsystemLocator::AddSubsystem()
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

	const auto& ret = m_mapSubsystem.emplace(TSubsystem::MatchType(), pSubsystem);
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

	const auto& iter = m_mapSubsystem.find(TSubsystem::MatchType());
	if ((iter == m_mapSubsystem.cend()) ||
		(iter->second == nullptr))
	{
		//::OutputDebugString("서브시스템을 찾을 수 없습니다!\n"); // 필요할 때만 사용
		return nullptr;
	}

	TSubsystem* pSubsystem = dynamic_cast<TSubsystem*>(iter->second);
	if (pSubsystem == nullptr)
	{
		::OutputDebugString("서브시스템을 캐스팅할 수 없습니다!\n");
		return nullptr;
	}

	return pSubsystem;
}