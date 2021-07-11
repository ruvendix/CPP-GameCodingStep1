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
	void RegisterSubsystem();

	template <typename TSubsystem>
	bool CheckDuplicatedSubsystem() const;

	template <typename TSubsystem, typename TNullSubsystem>
	TSubsystem* FindSubsystem() const;

	template <typename TSubsystem>
	void ExchangeSubsystem();

	void SetUp();
	void CleanUp();

private:
	// 내부 클래스에 넣어야 하지만 템플릿과 연관된 데이터이므로 그냥 둘게요.(내부 클래스에 넣으면 복잡해짐)
	std::unordered_map<ESubsystemType, ISubsystem*> m_mapSubsystem;
};