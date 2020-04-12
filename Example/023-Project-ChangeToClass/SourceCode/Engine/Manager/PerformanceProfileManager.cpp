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
	PerformanceProfileInfoPtr spInfo = FindInfo(ID);
	if (spInfo != nullptr)
	{
		spInfo->stopwatchTimer.StartTime();
		++spInfo->callCnt;

		//DEBUG_LOG_CATEGORY(PerformanceProfileMgr, "�̹� ��ϵ� ���������̿���! (%d)", ID);
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

	PerformanceProfileInfo& info = *(iter->second);
	info.totalPerformanceTime += info.stopwatchTimer.EndTime();
}

/*
��� �Լ��� �������� ���� ����� �����մϴ�.
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

		// ��� ���� �ð�(�� ���� �ð� / ȣ�� Ƚ��)
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
