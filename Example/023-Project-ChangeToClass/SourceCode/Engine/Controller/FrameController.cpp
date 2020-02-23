// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 게임의 프레임을 제어하는 컨트롤러입니다.
// 프레임 측정과 FPS에 따른 딜레이를 제어하는 기능이 있습니다.
// 프레임 측정에는 고해상도 측정 함수를 사용했습니다.
// 프레임 기법은 (가변 프레임 + 프레임 스키핑)을 사용했습니다.
// =====================================================================================

#include "PCH.h"
#include "FrameController.h"

#include "Context\ConfigContext.h"

namespace
{
	const Real32 FPS_UPDATE_TIME = 1.0f;
	const Int32 MAX_LIST_FPS = 10;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class FrameControllerHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(FrameControllerHelper);

public:
	static void UpdateDeltaTime();
	static void RefreshLimitedDeltaTime();

private:
	static Real32 m_limitedDeltaTime;
};

Real32 FrameControllerHelper::m_limitedDeltaTime = FPS_UPDATE_TIME / 60.0f;

/*
고해상도 타이머를 이용해서 델타타임을 갱신합니다.
CPU 틱에 의존하므로 멀티스레드에서는 정확하지 않을 수도 있다고 합니다.
참고 : http://www.tipssoft.com/bulletin/board.php?bo_table=FAQ&wr_id=735
*/
void FrameControllerHelper::UpdateDeltaTime()
{
	// 현재 시점의 CPU 틱을 알아내야 해요!
	LARGE_INTEGER currentTick;
	::QueryPerformanceCounter(&currentTick);

	LARGE_INTEGER CPUFrequency = FrameController::I()->m_CPUFrequency;
	LARGE_INTEGER& prevTick = FrameController::I()->m_prevTick;
	Real32& deltaTime = FrameController::I()->m_deltaTime;

	// 초단위의 델타타임을 계산합니다. (결과가 2.352라면 2.352초라는 의미)
	// (현재 시점의 CPU 틱 - 이전 시점의 CPU 틱)에 주파수를 나눠주면 됩니다.
	deltaTime = static_cast<Real32>(currentTick.QuadPart - prevTick.QuadPart) / (CPUFrequency.QuadPart);
	//DEBUG_LOG_CATEGORY(FrameController, "델타타임(%f)", deltaTime);

	EFrameRateType frameRateType = FrameController::I()->getFrameRateType();

	// 고정 프레임 레이트든 가변 프레임 레이트든 제한이 걸려있다면 그만큼 CPU를 슬립해야 해요!
	if ( (deltaTime < m_limitedDeltaTime) && 
		 (frameRateType != EFrameRateType::VARIABLE_UNLIMITED) )
	{
		// 남은 프레임 간격만큼 CPU를 슬립합니다.
		// 즉, 프로그램 속도에 영향을 미치지만 CPU 점유율은 감소됩니다.
		Uint32 sleepTime = static_cast<Uint32>((m_limitedDeltaTime - deltaTime) * 1000.0f);
		//DEBUG_LOG_CATEGORY(FrameController,
		//	"프레임 레이트에서 슬립 걸린다! 프레임 레이트(%s) 델타타임(%f) 슬립할 타임(%f)",
		//	(frameRateType == EFrameRateType::CONSTANT) ? ("고정") : ("가변"), deltaTime, static_cast<Real32>(sleepTime) * 0.001f);
		::SleepEx(sleepTime, TRUE);

		// 가변 프레임 레이트에서는 슬립했을 때만 델타타임을 고정합니다.
		// 즉, 델타타임은 설정한 제한값보다 빠를 수 없지만 설정한 제한값보다 느릴 수는 있어요!
		// 벌어진 간격만큼 갱신 및 렌더링하므로 프레임이 튀는 것처럼 보일 수 있죠...
		if (frameRateType == EFrameRateType::VARIABLE_LIMITED)
		{
			deltaTime = m_limitedDeltaTime;
		}
	}
	
	// 고정 프레임 레이트에서는 슬립에 관계없이 델타타임이 고정됩니다.
	// 즉, 컴퓨터 사양에 관계없이 델타타임이 일정하므로 컴퓨터마다 게임의 갱신 및 렌더링 상태가 다를 수 있습니다.
	// 어떤 컴퓨터는 씬이 변경되어서 플레이하고 있는데 어떤 컴퓨터는 아직 이전 씬에서 플레이하는 상황도 발생할 수 있죠...
	if (frameRateType == EFrameRateType::CONSTANT)
	{
		deltaTime = m_limitedDeltaTime;
	}

	// 초단위 기준으로 값을 출력합니다.
	//Real32 milliDeltaTime = deltaTime;
	//Real32 microDeltaTime = milliDeltaTime * 0.001f;
	//Real32 nanoDeltaTime  = microDeltaTime * 0.001f;
	//DEBUG_LOG_CATEGORY(FrameController, "MilliDeltaTime(%f) MicroDeltaTime(%f) NanoDeltaTime(%f)",
	//	milliDeltaTime, microDeltaTime, nanoDeltaTime);

	prevTick = currentTick;
}

/*
제한된 델타타임을 갱신합니다.
*/
void FrameControllerHelper::RefreshLimitedDeltaTime()
{
	Int32 limitedFrame = FrameController::I()->m_limitedFrame;

	// 무제한 프레임일 때는 델타타임을 0으로 고정할게요!
	if (limitedFrame == INT32_MAX)
	{
		m_limitedDeltaTime = 0.0f;
	}
	else
	{
		m_limitedDeltaTime = (FPS_UPDATE_TIME / FrameController::I()->m_limitedFrame);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_SINGLETON(FrameController);
DEFINE_LOG_CATEGORY(FrameController);

/*
고해상도 타이머의 주파수를 얻습니다.
주파수는 초당 진동수를 말하고, 단위는 Hz(헤르츠)입니다.
예를 들어 60Hz면 초당 60번 진동한다는 뜻입니다.
주기는 1사이클(Cycle)에 걸리는 시간을 말합니다.
사이클은 진동 한 번을 의미합니다. 따라서 주기는 = (1 / 주파수)입니다.
*/
void FrameController::Initialize()
{
	::QueryPerformanceFrequency(&m_CPUFrequency);
	::QueryPerformanceCounter(&m_prevTick);
}

/*
게임의 FPS와 델타타임을 갱신합니다.
FPS는 누적된 델타타임과 프레임 카운트를 이용해서 갱신합니다.
*/
void FrameController::UpdateFPSAndDeltatime()
{
	FrameControllerHelper::UpdateDeltaTime();

	m_accumulationFrameTime += m_deltaTime;
	++m_frameCnt;
	//DEBUG_LOG_CATEGORY(FrameController, "프레임 카운트(%d), 델타타임(%f)", m_frameCnt, m_deltaTime);

	// 1초가 넘어가면 FPS 갱신
	if (m_accumulationFrameTime >= FPS_UPDATE_TIME)
	{
		// FPS = 프레임 카운트 / 1초
		// 좀 더 정밀한 측정을 위해 (프레임 카운트 / 누적 프레임 시간)을 이용합니다.
		m_FPS = static_cast<Int32>(m_frameCnt / m_accumulationFrameTime);
		m_listFPS.push_back(m_FPS);
		DEBUG_LOG_CATEGORY(FrameController, "현재 프레임 카운트(%d) FPS(%d)", m_frameCnt, m_FPS);

		m_accumulationFrameTime -= FPS_UPDATE_TIME; // 짜투리 시간도 누적할게요!
		m_frameCnt = 0; // 프레임 카운트는 FPS 기준이므로 초기화해야 해요!
	}

	// 평균 FPS는 10개 기준입니다.
	if (m_listFPS.size() == MAX_LIST_FPS)
	{
		Int32 totalFPS = 0;
		for (auto& iter : m_listFPS)
		{
			totalFPS += iter;
		}
		
		DEBUG_LOG_CATEGORY(FrameController, "평균 FPS(%d)", totalFPS / MAX_LIST_FPS);
		m_listFPS.clear();
	}
}

/*
제한된 프레임값을 수정합니다.
*/
void FrameController::ModifyLimitedFrame(Int32 limitedFrame)
{
	if (m_frameRateType == EFrameRateType::VARIABLE_UNLIMITED)
	{
		DEBUG_LOG_CATEGORY(FrameController, "무제한 프레임이므로 값에 제한을 걸 수 없어요!");
		return;
	}

	m_limitedFrame = limitedFrame;
	FrameControllerHelper::RefreshLimitedDeltaTime();
}