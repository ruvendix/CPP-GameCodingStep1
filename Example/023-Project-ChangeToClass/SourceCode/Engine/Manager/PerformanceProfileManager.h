// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 함수의 수행 능력을 측정합니다.
// 여러 함수의 수행 능력을 동시에 측정할 수 있습니다.
// =====================================================================================

#ifndef PERFORMANCE_PROFILE_MGR__H__
#define PERFORMANCE_PROFILE_MGR__H__

#include "Element\NameTag.h"
#include "Timer\StopwatchTimer.h"

DECLARE_LOG_CATEGORY(PerformanceProfileMgr);

struct PerformanceProfileInfo
{
	std::string strFuncSig; // 측정되는 함수의 형식 (이름 포함)
	StopwatchTimer stopwatchTimer; // 수행 시간 측정
	Real32 totalPerformanceTime = 0.0f; // 총 수행 시간
	Uint32 callCnt = 0; // 호출 횟수
	Uint32 inputDataCnt = 0; // 입력된 주요 데이터 개수
};

using PerformanceProfileInfoPtr = std::shared_ptr<PerformanceProfileInfo>;
using MapPerformanceProfilerInfo = std::unordered_map<Uint32, PerformanceProfileInfoPtr>;

class PerformanceProfileMgr final
{
	DECLARE_PHOENIX_SINGLETON(PerformanceProfileMgr);

public:
	void Start(const std::string_view& szFuncSig, Int32 ID, Int32 inputDataCnt = 0);
	void End(Int32 ID); // 측정되는 함수의 식별을 위한 ID (__COUNTER__ 활용)
	void Report();

	PerformanceProfileInfoPtr FindInfo(Int32 ID) const;

private:
	MapPerformanceProfilerInfo m_mapPerformanceProfileInfo;
};

#endif