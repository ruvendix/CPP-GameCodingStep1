// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 함수의 수행 능력을 측정합니다.
// 여러 함수의 수행 능력을 동시에 측정할 수 있습니다.
// =====================================================================================

#include "PCH.h"
#include "PerformanceProfileManager.h"

DEFINE_LOG_CATEGORY(PerformanceProfileMgr);
DEFINE_PHOENIX_SINGLETON(PerformanceProfileMgr);

/*
ID를 이용해서 기존에 있는 정보인지 찾아보고 없으면 새로 생성합니다. (ID는 __COUNTER__)
새로 생성한 정보를 이용해서 프로파일 측정을 시작합니다.
*/
void PerformanceProfileMgr::Start(const std::string_view& szFuncSig, Int32 ID, Int32 inputDataCnt)
{
	PerformanceProfileInfoPtr spInfo = FindInfo(ID);
	if (spInfo != nullptr)
	{
		spInfo->stopwatchTimer.StartTime();
		++spInfo->callCnt;

		//DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "이미 등록된 프로파일이에요! (%d)", ID);
	}
	
	spInfo = std::make_shared<PerformanceProfileInfo>();
	spInfo->strFuncSig = szFuncSig;
	spInfo->inputDataCnt = inputDataCnt;
	spInfo->stopwatchTimer.StartTime();
	spInfo->callCnt = 1;

	auto ret = m_mapPerformanceProfileInfo.insert(std::make_pair(ID, nullptr));
	if (ret.second == true)
	{
		ret.first->second = spInfo;
	}
}

/*
프로파일 측정을 마칩니다.
*/
void PerformanceProfileMgr::End(Int32 ID)
{ 
	auto iter = m_mapPerformanceProfileInfo.find(ID);
	if (iter == m_mapPerformanceProfileInfo.cend())
	{
		DEFAULT_ERROR_HANDLER(EErrorType::NO_PERFORMANCE_PROFILE_INFO, ID);
		return;
	}

	PerformanceProfileInfo& info = *(iter->second);
	info.totalPerformanceTime += info.stopwatchTimer.EndTime();
}

/*
모든 함수의 프로파일 측정 결과를 보고합니다.
*/
void PerformanceProfileMgr::Report()
{
	DEBUG_LOG("##############################################################################################");
	DEBUG_LOG("PerformanceProfilerMgr Report");
	DEBUG_LOG("==============================================================================================");

	for (auto& iter : m_mapPerformanceProfileInfo)
	{
		PerformanceProfileInfoPtr spInfo = iter.second;

		DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "<%d - Performance profile report>", iter.first);
		DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "%s", spInfo->strFuncSig.c_str());
		DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "Input data count : %d", spInfo->inputDataCnt);
		DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "Function call count  : %d", spInfo->callCnt);
		DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "Total performance time : %f sec", spInfo->totalPerformanceTime);

		// 평균 수행 시간(총 수행 시간 / 호출 횟수)
		Real32 avgPerformanceTime = spInfo->totalPerformanceTime / spInfo->callCnt;
		DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "Average performance time : %f sec", avgPerformanceTime);
		DEBUG_LOG("==============================================================================================");
	}

	DEBUG_LOG("##############################################################################################");
}

PerformanceProfileMgr::PerformanceProfileInfoPtr PerformanceProfileMgr::FindInfo(Int32 ID) const
{
	auto iter = m_mapPerformanceProfileInfo.find(ID);
	if (iter != m_mapPerformanceProfileInfo.cend())
	{
		return iter->second;
	}

	return nullptr;
}
