// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 프레임과 관련된 시간을 다룹니다.
// =====================================================================================
#include "EnginePCH.h"
#include "FrameTimeManager.h"

/*
	프레임 관련 정보를 초기화합니다.
*/
void FrameTimeManager::SetUp()
{
	m_FPSTimer.setLoop(true);
	m_FPSTimer.setTargetTime(1.0f);

	m_deltaTimeStopwatch.StartTime();
	ModifyFixedDeltaTime(60);
}

/*
	프레임 관련 정보를 정리합니다.
	아직은 추가할 내용이 없어요.
*/
void FrameTimeManager::CleanUp()
{
	
}

/*
	프레임 시간을 갱신합니다.
	현재는 고정 프레임 레이트를 사용 중이므로
	남는 시간만큼 CPU에게 휴식을 줄게요.
*/
void FrameTimeManager::UpdateFrameTime()
{
	m_deltaTimeStopwatch.EndTime();
	Float elapsedTime = m_deltaTimeStopwatch.GetElapsedTime();
	Float sleepTime = m_fixedDeltaTime - elapsedTime;
	if (sleepTime >= 0.0f)
	{
		DWORD dwSleepTime = static_cast<DWORD>(sleepTime * CLOCKS_PER_SEC);
		::Sleep(dwSleepTime);
	}

	// 이전 프레임과 현재 프레임 사이의 시간은
	// 처리 경과 시간과 휴식 시간을 더한 값이에요!
	m_deltaTime = elapsedTime + sleepTime;
	//RX_SIMPLE_TRACE("%f", m_deltaTime);
	
	m_deltaTimeStopwatch.RestartTime();
	++m_frameCount; // 업데이트 ~ 렌더링을 거칠 때마다 1씩 증가합니다.

	// 타이머는 델타타임을 사용하고, 타임에서는 타이머를 사용합니다.
	// 이렇게 서로 엮이는 건 좋은 구조가 아니지만 델타타임의 초깃값이 0이라 문제는 없어요.
	// 되도록이면 이런 구조는 만들지 않는 걸 추천합니다!
	if (m_FPSTimer.UpdateTime() == true)
	{
		//RX_SIMPLE_TRACE("%d", m_frameCount);
		m_frameCount = 0;
	}
}