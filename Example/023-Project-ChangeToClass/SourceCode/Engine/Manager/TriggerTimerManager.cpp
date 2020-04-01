// =====================================================================================
// Copyright(c) 2019, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Ʈ���� Ÿ�̸Ӹ� �����մϴ�.
// Ʈ���� Ÿ�̸��� �̸��� Ű������ ���Ǹ� �ߺ��� �� �����ϴ�.
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
		pTriggerTimer->setFunc(func);
		pTriggerTimer->setRender(bRender);
		pTriggerTimer->setRepeat(bRepeat);
		DEBUG_LOG_CATEGORY(TriggerTimerMgr, "Ÿ�̸Ӱ� �̹� �����ϹǷ� �̸�(%s)�� ������ ��� �����͸� ����!", strTriggerTimer.c_str());

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
	for (auto iter = m_mapTriggerTimer.begin(); iter != iterEnd; /*���� ����*/)
	{
		TriggerTimer* pTriggerTimer = iter->second;
		CHECK_NULLPTR_CONTINUE(pTriggerTimer);

		if (pTriggerTimer->HasKeepTime() == false)
		{
			pTriggerTimer->AddElapsedTime();
		}

		// Ʈ���� Ÿ�Ӹ�ŭ ������ �����ϰ�, �ݺ� ������ �Ǿ����� ������ Ʈ���� Ÿ�̸Ӹ� �����ؾ� �ؿ�!
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
				DEBUG_LOG_CATEGORY(TriggerTimerMgr, "Ʈ���� Ÿ�̸Ӱ� ���ŵǾ����! (%s)", strTriggerTimer.data());
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
