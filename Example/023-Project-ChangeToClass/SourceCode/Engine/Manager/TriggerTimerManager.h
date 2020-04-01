// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Ʈ���� Ÿ�̸Ӹ� �����մϴ�.
// Ʈ���� Ÿ�̸��� �̸��� Ű������ ���Ǹ� �ߺ��� �� �����ϴ�.
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
	// ���ø��� �̿��ؼ� ��� �Լ� ������ ������ using���� �����ϴ� ���
	template <typename TElem>
	using ElemMemberFunc = void(TElem::*)(); // TriggerTimer���� ����ϴ� �ݹ� ���İ� �����ؾ� �ؿ�!

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
			// �̰� ������!
			return;
		}

		const auto& iter = m_mapTriggerTimer.find(strTriggerTimer);
		if (iter != m_mapTriggerTimer.cend())
		{			
			TriggerTimer* pTriggerTimer = iter->second;
			CHECK_NULLPTR(pTriggerTimer);
			
			// �̹� �����ϴ� Ʈ���� Ÿ�̸Ӷ�� �����͸� �������ݴϴ�.
			pTriggerTimer->StartTime();
			pTriggerTimer->setTime(triggerTime);
			pTriggerTimer->setKeepTime(keepTime);
			pTriggerTimer->setFunc(std::bind(elemMemberFunc, pElem));
			pTriggerTimer->setRender(bRender);
			pTriggerTimer->setRepeat(bRepeat);
			DEBUG_LOG_CATEGORY(TriggerTimerMgr, "Ÿ�̸Ӱ� �̹� �����ϹǷ� �̸�(%s)�� ������ ��� �����͸� ����!", strTriggerTimer.c_str());

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