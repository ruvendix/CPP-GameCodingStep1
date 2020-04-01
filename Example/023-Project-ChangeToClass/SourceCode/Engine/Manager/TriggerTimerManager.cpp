// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 트리거 타이머를 관리합니다.
// 트리거 타이머의 이름은 키값으로 사용되며 중복될 수 없습니다.
// =====================================================================================

#include "PCH.h"
#include "TriggerTimerManager.h"

DEFINE_LOG_CATEGORY(TriggerTimerMgr);
DEFINE_PHOENIX_SINGLETON(TriggerTimerMgr);

void TriggerTimerMgr::AddTriggerTimer(const std::string& strTriggerTimer, Real32 triggerTime, Real32 keepTime,
	const TriggerTimer::TCallback& func, bool bRender, bool bRepeat)
{
	if ( (bRepeat == true) && 
		 (triggerTime < keepTime) )
	{
		// 이건 오류임!
		return;
	}

	const auto& iter = m_mapTriggerTimer.find(strTriggerTimer);
	if (iter != m_mapTriggerTimer.cend())
	{
		TriggerTimer* pTriggerTimer = iter->second;
		CHECK_NULLPTR(pTriggerTimer);

		// 이미 존재하는 트리거 타이머라면 데이터를 갱신해줍니다.
		pTriggerTimer->StartTime();
		pTriggerTimer->setTime(triggerTime);
		pTriggerTimer->setKeepTime(keepTime);
		pTriggerTimer->setFunc(func);
		pTriggerTimer->setRender(bRender);
		pTriggerTimer->setRepeat(bRepeat);
		DEBUG_LOG_CATEGORY(TriggerTimerMgr, "타이머가 이미 존재하므로 이름(%s)을 제외한 모든 데이터를 갱신!", strTriggerTimer.c_str());

		return;
	}

	TriggerTimer* pTriggerTimer = trace_new TriggerTimer;
	pTriggerTimer->StartTime();
	pTriggerTimer->setTime(triggerTime);
	pTriggerTimer->setKeepTime(keepTime);
	pTriggerTimer->setFunc(func);
	pTriggerTimer->setRender(bRender);
	pTriggerTimer->setRepeat(bRepeat);

	auto ret = m_mapTriggerTimer.insert(std::make_pair(strTriggerTimer, nullptr));
	if (ret.second == true)
	{
		ret.first->second = pTriggerTimer;
	}

	return;
}

void TriggerTimerMgr::UpdateTriggerTimer()
{
	const auto& iterEnd = m_mapTriggerTimer.cend();
	for (auto iter = m_mapTriggerTimer.begin(); iter != iterEnd; /*증감 없음*/)
	{
		TriggerTimer* pTriggerTimer = iter->second;
		CHECK_NULLPTR_CONTINUE(pTriggerTimer);

		if (pTriggerTimer->HasKeepTime() == false)
		{
			pTriggerTimer->AddElapsedTime();
		}

		// 트리거 타임만큼 지나면 리셋하고, 반복 설정이 되어있지 않으면 트리거 타이머를 제거해야 해요!
		if (pTriggerTimer->IsTriggerTime())
		{
			if (pTriggerTimer->IsRender() == false)
			{
				pTriggerTimer->CallTriggerTimerFunc();
			}

			if (pTriggerTimer->IsExistKeepTime() == false)
			{
				pTriggerTimer->Reset();
			}
			else
			{
				pTriggerTimer->UpdateKeepTime();
				++iter;
				continue;
			}

			if (pTriggerTimer->IsRepeat() == false)
			{
				const std::string strTriggerTimer = iter->first;
				SAFE_DELETE(iter->second);
				iter = m_mapTriggerTimer.erase(iter);
				DEBUG_LOG_CATEGORY(TriggerTimerMgr, "트리거 타이머가 제거되었어요! (%s)", strTriggerTimer.data());
			}
			else
			{
				++iter;
			}
		}
		else
		{
			++iter;
		}
	}
}

void TriggerTimerMgr::CallTriggerTimerFuncForRender()
{
	for (const auto& iter : m_mapTriggerTimer)
	{
		TriggerTimer* pTriggerTimer = iter.second;
		CHECK_NULLPTR_CONTINUE(pTriggerTimer);
		
		if (pTriggerTimer->IsRender())
		{
			pTriggerTimer->CallTriggerTimerFunc();
		}
	}
}

void TriggerTimerMgr::DeleteTriggerTimer(const std::string_view& szTriggerTimer)
{
	auto iter = m_mapTriggerTimer.find(szTriggerTimer.data());
	if (iter != m_mapTriggerTimer.cend())
	{
		SAFE_DELETE(iter->second);
		m_mapTriggerTimer.erase(iter);
	}
}

void TriggerTimerMgr::Finalize()
{
	for (auto& iter : m_mapTriggerTimer)
	{
		SAFE_DELETE(iter.second);
	}
}
