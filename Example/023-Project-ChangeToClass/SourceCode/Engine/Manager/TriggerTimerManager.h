// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 트리거 타이머를 관리합니다.
// 트리거 타이머의 이름은 키값으로 사용되며 중복될 수 없습니다.
// =====================================================================================
#ifndef TRIGGER_TIMER_MGR_H
#define TRIGGER_TIMER_MGR_H

#include "Common\CommonType.h"
#include "Common\CommonNecessary.h"
#include "Common\CommonMacro.h"
#include "Element\NameTag.h"

#include "Timer\TriggerTimer.h"

DECLARE_LOG_CATEGORY(TriggerTimerMgr);

class TriggerTimerMgr final
{
	DECLARE_PHOENIX_SINGLETON(TriggerTimerMgr);

public:	
	// 템플릿을 이용해서 멤버 함수 포인터 형식을 using으로 선언하는 방법
	template <typename TElem>
	using ElemMemberFunc = void(TElem::*)(); // TriggerTimer에서 사용하는 콜백 형식과 동일해야 해요!

	void AddTriggerTimer(const std::string& strTriggerTimer, Real32 triggerTime, Real32 keepTime,
		const TriggerTimer::TCallback& func, bool bRender, bool bRepeat);
	void UpdateTriggerTimer();
	void CallTriggerTimerFuncForRender();
	void DeleteTriggerTimer(const std::string_view& szTriggerTimer);
	void Finalize();

	template <typename TElem>
	void AddTriggerTimer(const std::string& strTriggerTimer, Real32 triggerTime, Real32 keepTime,
		TElem* pElem, const ElemMemberFunc<TElem>& elemMemberFunc, bool bRender, bool bRepeat)
	{
		if (triggerTime < keepTime)
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
			pTriggerTimer->setFunc(std::bind(elemMemberFunc, pElem));
			pTriggerTimer->setRender(bRender);
			pTriggerTimer->setRepeat(bRepeat);
			DEBUG_LOG_CATEGORY(TriggerTimerMgr, "타이머가 이미 존재하므로 이름(%s)을 제외한 모든 데이터를 갱신!", strTriggerTimer.c_str());

			return;
		}

		TriggerTimer* pTriggerTimer = trace_new TriggerTimer;
		pTriggerTimer->StartTime();
		pTriggerTimer->setTime(triggerTime);
		pTriggerTimer->setFunc(std::bind(elemMemberFunc, pElem));
		pTriggerTimer->setRepeat(bRepeat);

		auto ret = m_mapTriggerTimer.insert(std::make_pair(strTriggerTimer, nullptr));
		if (ret.second == true)
		{
			ret.first->second = pTriggerTimer;
		}

		return;
	}

private:
	std::unordered_map<std::string, TriggerTimer*> m_mapTriggerTimer;
}; 

#endif