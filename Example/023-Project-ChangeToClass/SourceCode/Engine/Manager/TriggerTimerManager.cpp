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

DEFINE_LOG_CATEGORY(TriggerTimer);
DEFINE_SINGLETON(TriggerTimerMgr);

void TriggerTimerMgr::UpdateTriggerTimer()
{
	const auto& iterEnd = m_mapTriggerTimer.cend();
	for (auto iter = m_mapTriggerTimer.begin(); iter != iterEnd; /*���� ����*/)
	{
		if (iter->second == nullptr)
		{
			continue;
		}

		TriggerTimer* pTriggerTimer = iter->second;
		CHECK_NULLPTR(pTriggerTimer);
		pTriggerTimer->AddDeltaTime();

		// Ʈ���� Ÿ�Ӹ�ŭ ������ �����ϰ�, �ݺ� ������ �Ǿ����� ������ Ʈ���� Ÿ�̸Ӹ� �����ؾ� �ؿ�!
		if (pTriggerTimer->IsTriggerTime())
		{
			pTriggerTimer->CallTriggerTimerFunc();
			pTriggerTimer->Reset();

			if (pTriggerTimer->IsRepeat() == false)
			{
				const std::string_view& szTriggerTimer = iter->first;
				SAFE_DELETE(iter->second);
				iter = m_mapTriggerTimer.erase(iter);
				DEBUG_LOG_CATEGORY(TriggerTimer, "Ʈ���� Ÿ�̸Ӱ� ���ŵǾ����! (%s)", szTriggerTimer.data());
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

void TriggerTimerMgr::DeleteTriggerTimer(const std::string_view& szTriggerTimer)
{
	auto iter = m_mapTriggerTimer.find(szTriggerTimer.data());
	if (iter != m_mapTriggerTimer.cend())
	{
		SAFE_DELETE(iter->second);
		m_mapTriggerTimer.erase(iter);
	}
}

void TriggerTimerMgr::DeleteAllTriggerTimer()
{
	for (auto& iter : m_mapTriggerTimer)
	{
		SAFE_DELETE(iter.second);
	}
}
