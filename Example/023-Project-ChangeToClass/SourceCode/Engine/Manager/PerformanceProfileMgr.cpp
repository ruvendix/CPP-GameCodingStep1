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
#include "PerformanceProfileMgr.h"

DEFINE_LOG_CATEGORY(PerformanceProfileMgr);
DEFINE_PHOENIX_SINGLETON(PerformanceProfileMgr);

/*
ID를 이용해서 기존에 있는 정보인지 찾아보고 없으면 새로 생성합니다. (ID는 __COUNTER__)
새로 생성한 정보를 이용해서 프로파일 측정을 시작합니다.
*/
void PerformanceProfileMgr::Start(const std::string_view& szFuncSig, Int32 ID, Int32 inputDataCnt)
{
	auto iter = m_mapPerformanceProfileInfo.find(ID);
	if (iter != m_mapPerformanceProfileInfo.cend())
	{
		PerformanceProfileInfo* pPerformanceProfileInfo = iter->second;
		CHECK_NULLPTR_RETURN(pPerformanceProfileInfo, void);

		pPerformanceProfileInfo->stopwatchTimer.StartTime();
		++pPerformanceProfileInfo->callCnt;

		//DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "이미 등록된 프로파일이에요! (%d)", ID);
		return;
	}
	
	PerformanceProfileInfo* pPerformanceProfileInfo = trace_new PerformanceProfileInfo;
	pPerformanceProfileInfo->strFuncSig = szFuncSig;
	pPerformanceProfileInfo->inputDataCnt = inputDataCnt;
	pPerformanceProfileInfo->stopwatchTimer.StartTime();
	pPerformanceProfileInfo->callCnt = 1;

	m_mapPerformanceProfileInfo.insert(std::make_pair(ID, pPerformanceProfileInfo));
}

/*
프로파일 측정을 마칩니다.
*/
void PerformanceProfileMgr::End(Int32 ID)
{ 
	auto iter = m_mapPerformanceProfileInfo.find(ID);
	if (iter == m_mapPerformanceProfileInfo.cend())
	{
		ERROR_HANDLER_DETAIL(EErrorType::NO_PERFORMANCE_PROFILE_INFO, ID);
		return;
	}

	PerformanceProfileInfo* pPerformanceProfileInfo = iter->second;
	CHECK_NULLPTR_RETURN(pPerformanceProfileInfo, void);

	pPerformanceProfileInfo->totalPerformanceTime += pPerformanceProfileInfo->stopwatchTimer.EndTime();
}

/*
모든 함수의 프로파일 측정 결과를 보고합니다.
*/
void PerformanceProfileMgr::Report()
{
	DEBUG_LOG("==============================================================================================");
	
	for (auto& iter : m_mapPerformanceProfileInfo)
	{
		PerformanceProfileInfo* pPerformanceProfileInfo = iter.second;
		CHECK_NULLPTR_RETURN(pPerformanceProfileInfo, void);

		DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "<%d - Performance profile result>", iter.first);
		DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "%s", pPerformanceProfileInfo->strFuncSig.c_str());
		DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "Input data count : %d", pPerformanceProfileInfo->inputDataCnt);
		DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "Func call count  : %d", pPerformanceProfileInfo->callCnt);
		DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "Total performance time : %f sec", pPerformanceProfileInfo->totalPerformanceTime);

		// 평균 수행 시간(총 수행 시간 / 호출 횟수)
		Real32 avgPerformanceTime = pPerformanceProfileInfo->totalPerformanceTime / pPerformanceProfileInfo->callCnt;
		DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "Average performance time : %f sec", avgPerformanceTime);

		SAFE_DELETE(iter.second);
	}

	DEBUG_LOG("==============================================================================================");
}
