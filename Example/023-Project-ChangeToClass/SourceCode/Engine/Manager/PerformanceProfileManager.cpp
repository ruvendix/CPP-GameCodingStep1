// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �Լ��� ���� �ɷ��� �����մϴ�.
// ���� �Լ��� ���� �ɷ��� ���ÿ� ������ �� �ֽ��ϴ�.
// =====================================================================================

#include "PCH.h"
#include "PerformanceProfileManager.h"

DEFINE_LOG_CATEGORY(PerformanceProfileMgr);
DEFINE_PHOENIX_SINGLETON(PerformanceProfileMgr);

/*
ID�� �̿��ؼ� ������ �ִ� �������� ã�ƺ��� ������ ���� �����մϴ�. (ID�� __COUNTER__)
���� ������ ������ �̿��ؼ� �������� ������ �����մϴ�.
*/
void PerformanceProfileMgr::Start(const std::string_view& szFuncSig, Int32 ID, Int32 inputDataCnt)
{
	auto iter = m_mapPerformanceProfileInfo.find(ID);
	if (iter != m_mapPerformanceProfileInfo.cend())
	{
		PerformanceProfileInfo* pPerformanceProfileInfo = iter->second;
		CHECK_NULLPTR(pPerformanceProfileInfo);

		pPerformanceProfileInfo->stopwatchTimer.StartTime();
		++pPerformanceProfileInfo->callCnt;

		//DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "�̹� ��ϵ� ���������̿���! (%d)", ID);
		return;
	}
	
	PerformanceProfileInfo* pPerformanceProfileInfo = trace_new PerformanceProfileInfo;
	pPerformanceProfileInfo->strFuncSig = szFuncSig;
	pPerformanceProfileInfo->inputDataCnt = inputDataCnt;
	pPerformanceProfileInfo->stopwatchTimer.StartTime();
	pPerformanceProfileInfo->callCnt = 1;

	auto ret = m_mapPerformanceProfileInfo.insert(std::make_pair(ID, nullptr));
	if (ret.second == true)
	{
		ret.first->second = pPerformanceProfileInfo;
	}
}

/*
�������� ������ ��Ĩ�ϴ�.
*/
void PerformanceProfileMgr::End(Int32 ID)
{ 
	auto iter = m_mapPerformanceProfileInfo.find(ID);
	if (iter == m_mapPerformanceProfileInfo.cend())
	{
		DEFAULT_ERROR_HANDLER(EErrorType::NO_PERFORMANCE_PROFILE_INFO, ID);
		return;
	}

	PerformanceProfileInfo* pPerformanceProfileInfo = iter->second;
	CHECK_NULLPTR(pPerformanceProfileInfo);

	pPerformanceProfileInfo->totalPerformanceTime += pPerformanceProfileInfo->stopwatchTimer.EndTime();
}

/*
��� �Լ��� �������� ���� ����� �����մϴ�.
*/
void PerformanceProfileMgr::Report()
{
	DEBUG_LOG("==============================================================================================");
	
	for (auto& iter : m_mapPerformanceProfileInfo)
	{
		PerformanceProfileInfo* pPerformanceProfileInfo = iter.second;
		CHECK_NULLPTR(pPerformanceProfileInfo);

		DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "<%d - Performance profile ret>", iter.first);
		DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "%s", pPerformanceProfileInfo->strFuncSig.c_str());
		DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "Input data count : %d", pPerformanceProfileInfo->inputDataCnt);
		DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "Func call count  : %d", pPerformanceProfileInfo->callCnt);
		DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "Total performance time : %f sec", pPerformanceProfileInfo->totalPerformanceTime);

		// ��� ���� �ð�(�� ���� �ð� / ȣ�� Ƚ��)
		Real32 avgPerformanceTime = pPerformanceProfileInfo->totalPerformanceTime / pPerformanceProfileInfo->callCnt;
		DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "Average performance time : %f sec", avgPerformanceTime);

		SAFE_DELETE(iter.second);
	}

	DEBUG_LOG("==============================================================================================");
}