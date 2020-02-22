// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 트리거 타이머를 관리합니다.
// 트리거 타이머의 이름은 키값으로 사용되며 중복될 수 없습니다.
// =====================================================================================
#ifndef TRIGGER_TIMER_MANAGER_H
#define TRIGGER_TIMER_MANAGER_H

#include "Common\CommonType.h"
#include "Common\CommonNecessary.h"
#include "Common\CommonMacro.h"
#include "Element\NameTag.h"

#include "Timer\TriggerTimer.h"

DECLARE_LOG_CATEGORY(TriggerTimer);

class TriggerTimerMgr final
{
	DECLARE_SINGLETON(TriggerTimerMgr);

public:	
	// 템플릿을 이용해서 멤버 함수 포인터 형식을 using으로 선언하는 방법
	template <typename TElem>
	using ElemMemberFunc = void(TElem::*)(); // TriggerTimer에서 사용하는 콜백 형식과 동일해야 해요!

	void UpdateTriggerTimer();
	void DeleteTriggerTimer(const std::string_view& szTriggerTimer);
	void DeleteAllTriggerTimer();

	template <typename TElem>
	void AddTriggerTimer(const std::string& strTriggerTimer, Real32 triggerTime,
		TElem* pElem, const ElemMemberFunc<TElem>& elemMemberFunc, bool bRepeat)
	{
		const auto& iter = m_mapTriggerTimer.find(strTriggerTimer);
		if (iter != m_mapTriggerTimer.cend())
		{			
			TriggerTimer* pTriggerTimer = iter->second;
			CHECK_NULLPTR(pTriggerTimer);
			
			// 이미 존재하는 트리거 타이머라면 데이터를 갱신해줍니다.
			pTriggerTimer->setTime(triggerTime);
			pTriggerTimer->setFunc(std::bind(elemMemberFunc, pElem));
			pTriggerTimer->setRepeat(bRepeat);
			DEBUG_LOG_CATEGORY(TriggerTimer, "타이머가 이미 존재하므로 이름(%s)을 제외한 모든 데이터를 갱신!", strTriggerTimer);

			return;
		}

		TriggerTimer* pTriggerTimer = new TriggerTimer;
		CHECK_NULLPTR(pTriggerTimer);

		pTriggerTimer->setTime(triggerTime);
		pTriggerTimer->setFunc(std::bind(elemMemberFunc, pElem));
		pTriggerTimer->setRepeat(bRepeat);

		m_mapTriggerTimer.insert(std::make_pair(strTriggerTimer, pTriggerTimer));

		return;
	}

private:
	std::unordered_map<std::string, TriggerTimer*> m_mapTriggerTimer;
}; 

#endif