// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 고정 프레임 타임 매니저입니다.
// =====================================================================================
#include "EnginePCH.h"
#include "ConstantFrameManager.h"

class ConstantFrameManagerInside final
{
public:
	ConstantFrameManagerInside() = default;
	~ConstantFrameManagerInside() = default;

	void SetUp();
	void UpdateFrameTime(ConstantFrameManager& constantFrameManager);

private:
	Float m_fixedDeltaTime = 0.0f;
	Timer m_FPSTimer;
	Stopwatch m_deltaTimeStopwatch;
};

void ConstantFrameManagerInside::SetUp()
{
	m_FPSTimer.setLoop(true);
	m_FPSTimer.setTargetTime(1.0f);

	m_deltaTimeStopwatch.StartTime();
	m_fixedDeltaTime = ConstantFrameManager::ConvertFPS_ToFixedDeltaTime(60);
}

void ConstantFrameManagerInside::UpdateFrameTime(ConstantFrameManager& constantFrameManager)
{
	m_deltaTimeStopwatch.EndTime();
	Float elapsedTime = m_deltaTimeStopwatch.GetElapsedTime();
	Float sleepTime = m_fixedDeltaTime - elapsedTime;
	if (sleepTime >= 0.0f)
	{
		DWORD dwSleepTime = static_cast<DWORD>(sleepTime * CLOCKS_PER_SEC);
		::Sleep(dwSleepTime);
	}

	ConstantFrameManager::DataPtr spData = constantFrameManager.Data();

	// CF(고정 프레임)에서의 프레임 간격 시간은
	// 처리 경과 시간과 휴식 시간을 더한 값이에요!
	spData->SetDeltaTime(elapsedTime + sleepTime);
	//RX_SIMPLE_TRACE("%f", m_deltaTime);

	m_deltaTimeStopwatch.RestartTime();

	Int32 frameRate = spData->GetFrameRate();
	spData->SetFrameRate(frameRate + 1); // 업데이트 ~ 렌더링을 거칠 때마다 1씩 증가합니다.

	if (m_FPSTimer.UpdateTime() == true)
	{
		//RX_SIMPLE_TRACE("%d", m_frameRate);
		spData->SetFrameRate(0);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
ConstantFrameManager::ConstantFrameManager()
{
	m_spInside = std::make_unique<ConstantFrameManagerInside>();
}

/*
	프레임 관련 정보를 초기화합니다.
*/
void ConstantFrameManager::SetUp()
{
	m_spInside->SetUp();
}

/*
	프레임 관련 정보를 정리합니다.
	아직은 추가할 내용이 없어요.
*/
void ConstantFrameManager::CleanUp()
{
	
}

/*
	프레임 시간을 갱신합니다.
	현재는 고정 프레임 레이트를 사용 중이므로
	남는 시간만큼 CPU에게 휴식을 줄게요.
*/
void ConstantFrameManager::UpdateFrameTime()
{
	m_spInside->UpdateFrameTime(*this);
}