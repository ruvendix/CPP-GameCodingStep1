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

DEFINE_LOG_CATEGORY(TriggerTimer);
DEFINE_SINGLETON(TriggerTimerMgr);

void TriggerTimerMgr::UpdateTriggerTimer()
{
	const auto& iterEnd = m_mapTriggerTimer.cend();
	for (auto iter = m_mapTriggerTimer.begin(); iter != iterEnd; /*증감 없음*/)
	{
		if (iter->second == nullptr)
		{
			continue;
		}

		TriggerTimer* pTriggerTimer = iter->second;
		CHECK_NULLPTR(pTriggerTimer);
		pTriggerTimer->AddDeltaTime();

		// 트리거 타임만큼 지나면 리셋하고, 반복 설정이 되어있지 않으면 트리거 타이머를 제거해야 해요!
		if (pTriggerTimer->IsTriggerTime())
		{
			pTriggerTimer->CallTriggerTimerFunc();
			pTriggerTimer->Reset();

			if (pTriggerTimer->IsRepeat() == false)
			{
				const std::string_view& szTriggerTimer = iter->first;
				SAFE_DELETE(iter->second);
				iter = m_mapTriggerTimer.erase(iter);
				DEBUG_LOG_CATEGORY(TriggerTimer, "트리거 타이머가 제거되었어요! (%s)", szTriggerTimer.data());
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
