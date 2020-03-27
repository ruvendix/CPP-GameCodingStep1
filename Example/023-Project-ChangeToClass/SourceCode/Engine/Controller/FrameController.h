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

#ifndef FRAME_CONTROLLER__H__
#define FRAME_CONTROLLER__H__

#include "Common\CommonNecessary.h"
#include "Common\CommonType.h"
#include "Common\CommonMacro.h"
#include "Element\NameTag.h"

DECLARE_LOG_CATEGORY(FrameController);

enum class EFrameRateType : Int32
{
	CONSTANT = 0,
	VARIABLE_LIMITED,
	VARIABLE_UNLIMITED,
};

class FrameController final
{
	DECLARE_PHOENIX_SINGLETON(FrameController);
	FRIEND_WITH_HELPER(FrameControllerHelper);

public:
	void Initialize();
	void UpdateFrame();
	void ModifyLimitedFrame(Int32 limitedFrame);
	void ChangeFrameRateType(EFrameRateType frameRateType);

	void ResetTimeScale()
	{
		m_timeScale = 1.0f;
	}

	// "일시 정지, 시간 정지 효과" 등에서 활용하기 좋아요!
	void ZeroTimeScale()
	{
		m_timeScale = 0.0f;
	}

	Real32 getDeltaTime() const
	{
		return m_deltaTime;
	}

	Real32 getTimeScale() const
	{
		return m_timeScale;
	}

	Int32 getFPS() const
	{
		return m_FPS;
	}

	Int32 getAvgFPS() const
	{
		return m_avgFPS;
	}

	Int32 getInputFPS() const
	{
		return m_inputFPS;
	}

	void setTimeScale(Real32 timeScale)
	{
		m_timeScale = timeScale;
	}

	EFrameRateType getFrameRateType() const
	{
		return m_frameRateType;
	}

private:
	void OnTrigger_RefreshFPS();

	std::list<Int32> m_listFPS; // 평균 프레임값을 구하기 위해 사용합니다.

	Int32 m_frameCnt = 0; // 게임 루프당 프레임 하나입니다.
	Int32 m_FPS = 0; // 초당 프레임 개수입니다. (Frame Per Second)
	Int32 m_avgFPS = 0; // 평균 FPS입니다. (10개 기준)
	Int32 m_limitedFrame = 60;
	Int32 m_inputFPS = 30; // 입력 FPS입니다.

	Real32 m_accumulationFrameTime = 0.0f;
	Real32 m_timeScale = 1.0f; // 값이 크면 빨라지고, 작으면 느려집니다.
	Real32 m_deltaTime = 0.0f; // 이전 프레임과 현재 프레임의 간격입니다. (고정, 가변 둘 다 가능)

	LARGE_INTEGER m_CPUFrequency;
	LARGE_INTEGER m_prevTick;

	EFrameRateType m_frameRateType = EFrameRateType::CONSTANT;
};

#endif