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
#include "Manager\TriggerTimerManager.h"

namespace
{
	const Real32 FPS_UPDATE_TIME = 1.0f;
	const Int32 MAX_FPS_CNT = 10;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class FrameControllerHelper final
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(FrameControllerHelper);

public:
	using UpdateDeltaTimeCallback = std::function<void()>;

	static void UpdateDeltaTime();
	static void RefreshLimitedDeltaTime();
	static void ChangeUpdateDeltaTimeCallback(EFrameRateType frameRateType);

	static void OnCallback_UpdateDeltaTime_ConstantFrameRate();
	static void OnCallback_UpdateDeltaTime_VariableLimitedFrameRate();
	static void OnCallback_UpdateDeltaTime_VariableUnlimitedFrameRate();

private:
	static Real32 m_limitedDeltaTime;
	static UpdateDeltaTimeCallback m_updateDeltaTimeCalllback; // 전략 패턴
};

Real32 FrameControllerHelper::m_limitedDeltaTime = FPS_UPDATE_TIME / 60.0f;
FrameControllerHelper::UpdateDeltaTimeCallback FrameControllerHelper::m_updateDeltaTimeCalllback = OnCallback_UpdateDeltaTime_ConstantFrameRate;

/*
고해상도 타이머를 이용해서 델타타임을 갱신합니다.
CPU 틱에 의존하므로 멀티스레드에서는 정확하지 않을 수도 있다고 합니다.
참고 : http://www.tipssoft.com/bulletin/board.php?bo_table=FAQ&wr_id=735
*/
void FrameControllerHelper::UpdateDeltaTime()
{
	m_updateDeltaTimeCalllback();
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

void FrameControllerHelper::ChangeUpdateDeltaTimeCallback(EFrameRateType frameRateType)
{
	switch (frameRateType)
	{
	case EFrameRateType::CONSTANT:
	{
		m_updateDeltaTimeCalllback = OnCallback_UpdateDeltaTime_ConstantFrameRate;
		RefreshLimitedDeltaTime();
		FrameController::I()->m_deltaTime = m_limitedDeltaTime;
		break;
	}

	case EFrameRateType::VARIABLE_LIMITED:
	{
		m_updateDeltaTimeCalllback = OnCallback_UpdateDeltaTime_VariableLimitedFrameRate;
		RefreshLimitedDeltaTime();
		break;
	}

	case EFrameRateType::VARIABLE_UNLIMITED:
	{
		m_updateDeltaTimeCalllback = OnCallback_UpdateDeltaTime_VariableUnlimitedFrameRate;
		break;
	}

	default:
	{
		DEFAULT_ERROR_HANDLER(EErrorType::UNKNOWN_FRAME_RATE_TYPE);
		break;
	}
	}
}

/*
고정 프레임 레이트에서는 델타타임에 변화가 없으므로 제한된 델타타임만큼 CPU를 슬립해주면 됩니다.
저사양에서는 처리 속도가 느려도 델타타임이 고정되어있어서 게임 화면 갱신이 늦는 것처럼 보일 거에요.
고사양에서는 처리 속도가 빨라도 델타타임이 고정되어있어서 안정된 프레임으로 게임을 즐길 수 있죠. (하드웨어 낭비...)
FPS를 너무 높게 고정해버리면 슬립의 의미가 사라지므로 실제 시간 1초마다 FPS를 갱신하게 되면 가변 프레임 레이트처럼 되어버립니다.
*/
void FrameControllerHelper::OnCallback_UpdateDeltaTime_ConstantFrameRate()
{
	// 현재 시점의 CPU 틱을 알아내야 해요!
	LARGE_INTEGER currentTick;
	::QueryPerformanceCounter(&currentTick);

	LARGE_INTEGER& prevTick = FrameController::I()->m_prevTick;
	Real32& deltaTime = FrameController::I()->m_deltaTime;

	// 게임 실행 후 첫 프레임 때에요!
	// 이 때는 CPU를 슬립하지 않고 델타타임만 제한된 델타임으로 조정할게요.
	if (deltaTime == 0.0f)
	{
		// 고정 프레임 레이트에서는 델타타임을 제한된 델타타임으로 고정해야 해요!
		deltaTime = m_limitedDeltaTime;
		prevTick = currentTick;
		return;
	}

	// 초단위의 델타타임을 계산합니다. (결과가 2.352라면 2.352초라는 의미)
	// (현재 시점의 CPU 틱 - 이전 시점의 CPU 틱)에 주파수를 나눠주면 됩니다.
	deltaTime = static_cast<Real32>(currentTick.QuadPart - prevTick.QuadPart) / (FrameController::I()->m_CPUFrequency.QuadPart);
	//DEBUG_LOG_CATEGORY(FrameController, "델타타임(%f)", deltaTime);

	// 제한된 델타타임보다 빠르다면 제한된 델타타임만큼 CPU를 슬립해야 해요!
	if (deltaTime < m_limitedDeltaTime)
	{		
		Real32 sleepTime = (m_limitedDeltaTime - deltaTime);
		::SleepEx(static_cast<Uint32>(sleepTime * 1000.0f), FALSE);
		//DEBUG_LOG_CATEGORY(FrameController, "고정 프레임 레이트에서 슬립! 델타타임(%f) 슬립할 타임(%f)", deltaTime, sleepTime);
		::QueryPerformanceCounter(&prevTick); // 슬립했으므로 여기서 다시 시작!
	}
	else
	{
		prevTick = currentTick;
	}

	// 고정 프레임 레이트에서는 델타타임을 제한된 델타타임으로 고정해야 해요!
	deltaTime = m_limitedDeltaTime;
}

/*
가변 제한 프레임 레이트에서는 제한된 델타타임보다 빠를 때 제한된 델타타임만큼 CPU를 슬립해주면 됩니다.
저사양에서는 처리 속도가 느려도 델타타임이 가변적이라서 게임 화면 갱신이 들쑥날쑥하게 보일 거에요.
고사양에서는 처리 속도가 느릴 때 게임 화면 갱신이 들쑥날쑥해지고, 처리 속도가 빠를 때는 고정 프레임 레이트처럼 느껴질 거에요.
*/
void FrameControllerHelper::OnCallback_UpdateDeltaTime_VariableLimitedFrameRate()
{
	// 현재 시점의 CPU 틱을 알아내야 해요!
	LARGE_INTEGER currentTick;
	::QueryPerformanceCounter(&currentTick);

	LARGE_INTEGER& prevTick = FrameController::I()->m_prevTick;
	Real32& deltaTime = FrameController::I()->m_deltaTime;

	// 게임 실행 후 첫 프레임 때에요!
	// 이 때는 CPU를 슬립하지 않고 델타타임만 제한된 델타임으로 조정할게요.
	if (deltaTime == 0.0f)
	{
		deltaTime = m_limitedDeltaTime;
		prevTick = currentTick;
		return;
	}

	// 초단위의 델타타임을 계산합니다. (결과가 2.352라면 2.352초라는 의미)
	// (현재 시점의 CPU 틱 - 이전 시점의 CPU 틱)에 주파수를 나눠주면 됩니다.
	deltaTime = static_cast<Real32>(currentTick.QuadPart - prevTick.QuadPart) / (FrameController::I()->m_CPUFrequency.QuadPart);
	//DEBUG_LOG_CATEGORY(FrameController, "델타타임(%f)", deltaTime);

	// 제한된 델타타임보다 빠르다면 제한된 델타타임만큼 CPU를 슬립해야 해요!
	if (deltaTime < m_limitedDeltaTime)
	{
		Real32 sleepTime = (m_limitedDeltaTime - deltaTime);
		::SleepEx(static_cast<Uint32>(sleepTime * 1000.0f), FALSE);
		//DEBUG_LOG_CATEGORY(FrameController, "가변 제한 프레임 레이트에서 슬립! 델타타임(%f) 슬립할 타임(%f)", deltaTime, sleepTime);
		::QueryPerformanceCounter(&prevTick); // 슬립했으므로 여기서 다시 시작!

		// 가변 제한 프레임 레이트에서 델타타임이 제한된 델타타임보다 빠르다면 제한된 델타타임으로 덮어야 해요!
		// 고정 프레임 레이트처럼 이미 CPU를 슬립한 후이므로 실제 시간과 맞아떨어지죠.
		deltaTime = m_limitedDeltaTime;
	}
	else
	{
		prevTick = currentTick;
	}

	// 초단위 기준으로 값을 출력합니다.
	//Real32 milliDeltaTime = deltaTime;
	//Real32 microDeltaTime = milliDeltaTime * 0.001f;
	//Real32 nanoDeltaTime  = microDeltaTime * 0.001f;
	//DEBUG_LOG_CATEGORY(FrameController, "MilliDeltaTime(%f) MicroDeltaTime(%f) NanoDeltaTime(%f)", milliDeltaTime, microDeltaTime, nanoDeltaTime);
}

/*
가변 무한 프레임 레이트에서는 CPU 슬립을 하지 않습니다.
저사양에서는 가변 제한 프레임과 다를 게 없어요.
고사양에서는 처리 속도가 느리면 가변 제한 프레임과 다를 게 없지만, 처리 속도가 빠를 때는 게임 화면 갱신이 매우 빠르게 변할 거에요.
*/
void FrameControllerHelper::OnCallback_UpdateDeltaTime_VariableUnlimitedFrameRate()
{
	// 현재 시점의 CPU 틱을 알아내야 해요!
	LARGE_INTEGER currentTick;
	::QueryPerformanceCounter(&currentTick);

	LARGE_INTEGER& prevTick = FrameController::I()->m_prevTick;
	Real32& deltaTime = FrameController::I()->m_deltaTime;

	// 초단위의 델타타임을 계산합니다. (결과가 2.352라면 2.352초라는 의미)
	// (현재 시점의 CPU 틱 - 이전 시점의 CPU 틱)에 주파수를 나눠주면 됩니다.
	deltaTime = static_cast<Real32>(currentTick.QuadPart - prevTick.QuadPart) / (FrameController::I()->m_CPUFrequency.QuadPart);
	//DEBUG_LOG_CATEGORY(FrameController, "델타타임(%f)", deltaTime);

	prevTick = currentTick;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_PHOENIX_SINGLETON(FrameController);
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

	TriggerTimerMgr::I()->AddTriggerTimer("FPS", 1.0f, 0.0f, this, &FrameController::OnTrigger_RefreshFPS, false, true);
}

/*
게임의 FPS와 델타타임을 갱신합니다.
FPS는 누적된 델타타임과 프레임 카운트를 이용해서 갱신합니다.
델타타임을 누적하게 되면 실제 시간이 아니라 게임 시간을 기준으로 봐야 합니다.
*/
void FrameController::UpdateFrame()
{
	++m_frameCnt;
	FrameControllerHelper::UpdateDeltaTime();
}

/*
제한된 프레임값을 수정합니다.
*/
void FrameController::ModifyLimitedFrame(Int32 limitedFrame)
{
	if (m_frameRateType == EFrameRateType::VARIABLE_UNLIMITED)
	{
		DEFAULT_ERROR_HANDLER(EErrorType::NO_FRAME_LIMITED_ON_UNLIMITED_FRAME_RATE);
		return;
	}

	m_limitedFrame = limitedFrame;
	FrameControllerHelper::RefreshLimitedDeltaTime();
}

void FrameController::ChangeFrameRateType(EFrameRateType frameRateType)
{
	m_frameRateType = frameRateType;
	FrameControllerHelper::ChangeUpdateDeltaTimeCallback(m_frameRateType);
}

/*
실제 시간 1초마다 FPS를 갱신합니다.
FPS 10개가 쌓이면 평균 FPS를 계산합니다.
프레임 레이트 타입에 관계없이 1초마다 갱신됩니다.
FPS => Frame Per Second, 초당 프레임 개수
*/
void FrameController::OnTrigger_RefreshFPS()
{
	// 좀 더 정밀한 측정을 위해 (프레임 카운트 / 누적 프레임 시간)을 이용하기도 해요!
	//m_FPS = static_cast<Int32>(m_frameCnt / m_accumulationFrameTime);

	// 정밀한 측정이 아니어도 FPS는 꽤 정확해요!
	m_FPS = m_frameCnt;

	m_listFPS.push_back(m_FPS);
	DEBUG_LOG_CATEGORY(FrameController, "현재 프레임 카운트(%d) FPS(%d)", m_frameCnt, m_FPS);

	m_accumulationFrameTime -= FPS_UPDATE_TIME; // 짜투리 시간도 누적할게요!
	m_frameCnt = 0; // 프레임 카운트는 FPS 기준이므로 초기화해야 해요!

	// 평균 FPS는 10개 기준!
	if (m_listFPS.size() == MAX_FPS_CNT)
	{
		Int32 totalFPS = 0;
		for (auto& iter : m_listFPS)
		{
			totalFPS += iter;
		}

		m_avgFPS = totalFPS / MAX_FPS_CNT;
		DEBUG_LOG_CATEGORY(FrameController, "평균 FPS(%d)", m_avgFPS);
		m_listFPS.clear();
	}
}
