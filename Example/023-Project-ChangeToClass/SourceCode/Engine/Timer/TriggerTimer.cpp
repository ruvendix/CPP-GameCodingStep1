// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 설정된 시간마다 이벤트가 발생하는 타이머입니다.
// 반복으로 설정되어있으면 이벤트가 주기적으로 발생합니다.
// 단독으로 사용될 수는 없고 매니저를 이용해야 합니다.
// =====================================================================================

#include "PCH.h"
#include "TriggerTimer.h"

#include "Controller\FrameController.h"

/*
경과 시간에 시간 간격을 더합니다.
게임 시간이 아니라 실제 시간만큼 더해야 합니다.
*/
void TriggerTimer::AddElapsedTime()
{
	EndTime();
	m_triggerElaspedTime += getElaspedTime();
	SwapTime();

	//DEBUG_LOG("(%f)초 체크!", m_elapsedTime);

	//m_elapsedTime += FrameController::I()->getDeltaTime();
	//static Int32 cnt = 0;
	//DEBUG_LOG("%f초 체크! (%f) (%d)", m_elapsedTime, FrameController::I()->getDeltaTime(), ++cnt);
}

void TriggerTimer::UpdateKeepTime()
{
	m_keepTime -= FrameController::I()->getDeltaTime();
}
