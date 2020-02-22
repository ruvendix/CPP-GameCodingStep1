// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Ʈ���� Ÿ�̸Ӹ� �����մϴ�.
// Ʈ���� Ÿ�̸��� �̸��� Ű������ ���Ǹ� �ߺ��� �� �����ϴ�.
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
	// ���ø��� �̿��ؼ� ��� �Լ� ������ ������ using���� �����ϴ� ���
	template <typename TElem>
	using ElemMemberFunc = void(TElem::*)(); // TriggerTimer���� ����ϴ� �ݹ� ���İ� �����ؾ� �ؿ�!

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
			
			// �̹� �����ϴ� Ʈ���� Ÿ�̸Ӷ�� �����͸� �������ݴϴ�.
			pTriggerTimer->setTime(triggerTime);
			pTriggerTimer->setFunc(std::bind(elemMemberFunc, pElem));
			pTriggerTimer->setRepeat(bRepeat);
			DEBUG_LOG_CATEGORY(TriggerTimer, "Ÿ�̸Ӱ� �̹� �����ϹǷ� �̸�(%s)�� ������ ��� �����͸� ����!", strTriggerTimer);

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