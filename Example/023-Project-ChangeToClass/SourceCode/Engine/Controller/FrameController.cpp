// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������ �������� �����ϴ� ��Ʈ�ѷ��Դϴ�.
// ������ ������ FPS�� ���� �����̸� �����ϴ� ����� �ֽ��ϴ�.
// ������ �������� ���ػ� ���� �Լ��� ����߽��ϴ�.
// ������ ����� (���� ������ + ������ ��Ű��)�� ����߽��ϴ�.
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
	static UpdateDeltaTimeCallback m_updateDeltaTimeCalllback; // ���� ����
};

Real32 FrameControllerHelper::m_limitedDeltaTime = FPS_UPDATE_TIME / 60.0f;
FrameControllerHelper::UpdateDeltaTimeCallback FrameControllerHelper::m_updateDeltaTimeCalllback = OnCallback_UpdateDeltaTime_ConstantFrameRate;

/*
���ػ� Ÿ�̸Ӹ� �̿��ؼ� ��ŸŸ���� �����մϴ�.
CPU ƽ�� �����ϹǷ� ��Ƽ�����忡���� ��Ȯ���� ���� ���� �ִٰ� �մϴ�.
���� : http://www.tipssoft.com/bulletin/board.php?bo_table=FAQ&wr_id=735
*/
void FrameControllerHelper::UpdateDeltaTime()
{
	m_updateDeltaTimeCalllback();
}

/*
���ѵ� ��ŸŸ���� �����մϴ�.
*/
void FrameControllerHelper::RefreshLimitedDeltaTime()
{
	Int32 limitedFrame = FrameController::I()->m_limitedFrame;

	// ������ �������� ���� ��ŸŸ���� 0���� �����ҰԿ�!
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
���� ������ ����Ʈ������ ��ŸŸ�ӿ� ��ȭ�� �����Ƿ� ���ѵ� ��ŸŸ�Ӹ�ŭ CPU�� �������ָ� �˴ϴ�.
����翡���� ó�� �ӵ��� ������ ��ŸŸ���� �����Ǿ��־ ���� ȭ�� ������ �ʴ� ��ó�� ���� �ſ���.
���翡���� ó�� �ӵ��� ���� ��ŸŸ���� �����Ǿ��־ ������ ���������� ������ ��� �� ����. (�ϵ���� ����...)
FPS�� �ʹ� ���� �����ع����� ������ �ǹ̰� ������Ƿ� ���� �ð� 1�ʸ��� FPS�� �����ϰ� �Ǹ� ���� ������ ����Ʈó�� �Ǿ�����ϴ�.
*/
void FrameControllerHelper::OnCallback_UpdateDeltaTime_ConstantFrameRate()
{
	// ���� ������ CPU ƽ�� �˾Ƴ��� �ؿ�!
	LARGE_INTEGER currentTick;
	::QueryPerformanceCounter(&currentTick);

	LARGE_INTEGER& prevTick = FrameController::I()->m_prevTick;
	Real32& deltaTime = FrameController::I()->m_deltaTime;

	// ���� ���� �� ù ������ ������!
	// �� ���� CPU�� �������� �ʰ� ��ŸŸ�Ӹ� ���ѵ� ��Ÿ������ �����ҰԿ�.
	if (deltaTime == 0.0f)
	{
		// ���� ������ ����Ʈ������ ��ŸŸ���� ���ѵ� ��ŸŸ������ �����ؾ� �ؿ�!
		deltaTime = m_limitedDeltaTime;
		prevTick = currentTick;
		return;
	}

	// �ʴ����� ��ŸŸ���� ����մϴ�. (����� 2.352��� 2.352�ʶ�� �ǹ�)
	// (���� ������ CPU ƽ - ���� ������ CPU ƽ)�� ���ļ��� �����ָ� �˴ϴ�.
	deltaTime = static_cast<Real32>(currentTick.QuadPart - prevTick.QuadPart) / (FrameController::I()->m_CPUFrequency.QuadPart);
	//DEBUG_LOG_CATEGORY(FrameController, "��ŸŸ��(%f)", deltaTime);

	// ���ѵ� ��ŸŸ�Ӻ��� �����ٸ� ���ѵ� ��ŸŸ�Ӹ�ŭ CPU�� �����ؾ� �ؿ�!
	if (deltaTime < m_limitedDeltaTime)
	{		
		Real32 sleepTime = (m_limitedDeltaTime - deltaTime);
		::SleepEx(static_cast<Uint32>(sleepTime * 1000.0f), FALSE);
		//DEBUG_LOG_CATEGORY(FrameController, "���� ������ ����Ʈ���� ����! ��ŸŸ��(%f) ������ Ÿ��(%f)", deltaTime, sleepTime);
		::QueryPerformanceCounter(&prevTick); // ���������Ƿ� ���⼭ �ٽ� ����!
	}
	else
	{
		prevTick = currentTick;
	}

	// ���� ������ ����Ʈ������ ��ŸŸ���� ���ѵ� ��ŸŸ������ �����ؾ� �ؿ�!
	deltaTime = m_limitedDeltaTime;
}

/*
���� ���� ������ ����Ʈ������ ���ѵ� ��ŸŸ�Ӻ��� ���� �� ���ѵ� ��ŸŸ�Ӹ�ŭ CPU�� �������ָ� �˴ϴ�.
����翡���� ó�� �ӵ��� ������ ��ŸŸ���� �������̶� ���� ȭ�� ������ �龦�����ϰ� ���� �ſ���.
���翡���� ó�� �ӵ��� ���� �� ���� ȭ�� ������ �龦����������, ó�� �ӵ��� ���� ���� ���� ������ ����Ʈó�� ������ �ſ���.
*/
void FrameControllerHelper::OnCallback_UpdateDeltaTime_VariableLimitedFrameRate()
{
	// ���� ������ CPU ƽ�� �˾Ƴ��� �ؿ�!
	LARGE_INTEGER currentTick;
	::QueryPerformanceCounter(&currentTick);

	LARGE_INTEGER& prevTick = FrameController::I()->m_prevTick;
	Real32& deltaTime = FrameController::I()->m_deltaTime;

	// ���� ���� �� ù ������ ������!
	// �� ���� CPU�� �������� �ʰ� ��ŸŸ�Ӹ� ���ѵ� ��Ÿ������ �����ҰԿ�.
	if (deltaTime == 0.0f)
	{
		deltaTime = m_limitedDeltaTime;
		prevTick = currentTick;
		return;
	}

	// �ʴ����� ��ŸŸ���� ����մϴ�. (����� 2.352��� 2.352�ʶ�� �ǹ�)
	// (���� ������ CPU ƽ - ���� ������ CPU ƽ)�� ���ļ��� �����ָ� �˴ϴ�.
	deltaTime = static_cast<Real32>(currentTick.QuadPart - prevTick.QuadPart) / (FrameController::I()->m_CPUFrequency.QuadPart);
	//DEBUG_LOG_CATEGORY(FrameController, "��ŸŸ��(%f)", deltaTime);

	// ���ѵ� ��ŸŸ�Ӻ��� �����ٸ� ���ѵ� ��ŸŸ�Ӹ�ŭ CPU�� �����ؾ� �ؿ�!
	if (deltaTime < m_limitedDeltaTime)
	{
		Real32 sleepTime = (m_limitedDeltaTime - deltaTime);
		::SleepEx(static_cast<Uint32>(sleepTime * 1000.0f), FALSE);
		//DEBUG_LOG_CATEGORY(FrameController, "���� ���� ������ ����Ʈ���� ����! ��ŸŸ��(%f) ������ Ÿ��(%f)", deltaTime, sleepTime);
		::QueryPerformanceCounter(&prevTick); // ���������Ƿ� ���⼭ �ٽ� ����!

		// ���� ���� ������ ����Ʈ���� ��ŸŸ���� ���ѵ� ��ŸŸ�Ӻ��� �����ٸ� ���ѵ� ��ŸŸ������ ����� �ؿ�!
		// ���� ������ ����Ʈó�� �̹� CPU�� ������ ���̹Ƿ� ���� �ð��� �¾ƶ�������.
		deltaTime = m_limitedDeltaTime;
	}
	else
	{
		prevTick = currentTick;
	}

	// �ʴ��� �������� ���� ����մϴ�.
	//Real32 milliDeltaTime = deltaTime;
	//Real32 microDeltaTime = milliDeltaTime * 0.001f;
	//Real32 nanoDeltaTime  = microDeltaTime * 0.001f;
	//DEBUG_LOG_CATEGORY(FrameController, "MilliDeltaTime(%f) MicroDeltaTime(%f) NanoDeltaTime(%f)", milliDeltaTime, microDeltaTime, nanoDeltaTime);
}

/*
���� ���� ������ ����Ʈ������ CPU ������ ���� �ʽ��ϴ�.
����翡���� ���� ���� �����Ӱ� �ٸ� �� �����.
���翡���� ó�� �ӵ��� ������ ���� ���� �����Ӱ� �ٸ� �� ������, ó�� �ӵ��� ���� ���� ���� ȭ�� ������ �ſ� ������ ���� �ſ���.
*/
void FrameControllerHelper::OnCallback_UpdateDeltaTime_VariableUnlimitedFrameRate()
{
	// ���� ������ CPU ƽ�� �˾Ƴ��� �ؿ�!
	LARGE_INTEGER currentTick;
	::QueryPerformanceCounter(&currentTick);

	LARGE_INTEGER& prevTick = FrameController::I()->m_prevTick;
	Real32& deltaTime = FrameController::I()->m_deltaTime;

	// �ʴ����� ��ŸŸ���� ����մϴ�. (����� 2.352��� 2.352�ʶ�� �ǹ�)
	// (���� ������ CPU ƽ - ���� ������ CPU ƽ)�� ���ļ��� �����ָ� �˴ϴ�.
	deltaTime = static_cast<Real32>(currentTick.QuadPart - prevTick.QuadPart) / (FrameController::I()->m_CPUFrequency.QuadPart);
	//DEBUG_LOG_CATEGORY(FrameController, "��ŸŸ��(%f)", deltaTime);

	prevTick = currentTick;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_PHOENIX_SINGLETON(FrameController);
DEFINE_LOG_CATEGORY(FrameController);

/*
���ػ� Ÿ�̸��� ���ļ��� ����ϴ�.
���ļ��� �ʴ� �������� ���ϰ�, ������ Hz(�츣��)�Դϴ�.
���� ��� 60Hz�� �ʴ� 60�� �����Ѵٴ� ���Դϴ�.
�ֱ�� 1����Ŭ(Cycle)�� �ɸ��� �ð��� ���մϴ�.
����Ŭ�� ���� �� ���� �ǹ��մϴ�. ���� �ֱ�� = (1 / ���ļ�)�Դϴ�.
*/
void FrameController::Initialize()
{
	::QueryPerformanceFrequency(&m_CPUFrequency);
	::QueryPerformanceCounter(&m_prevTick);

	TriggerTimerMgr::I()->AddTriggerTimer("FPS", 1.0f, 0.0f, this, &FrameController::OnTrigger_RefreshFPS, false, true);
}

/*
������ FPS�� ��ŸŸ���� �����մϴ�.
FPS�� ������ ��ŸŸ�Ӱ� ������ ī��Ʈ�� �̿��ؼ� �����մϴ�.
��ŸŸ���� �����ϰ� �Ǹ� ���� �ð��� �ƴ϶� ���� �ð��� �������� ���� �մϴ�.
*/
void FrameController::UpdateFrame()
{
	++m_frameCnt;
	FrameControllerHelper::UpdateDeltaTime();
}

/*
���ѵ� �����Ӱ��� �����մϴ�.
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
���� �ð� 1�ʸ��� FPS�� �����մϴ�.
FPS 10���� ���̸� ��� FPS�� ����մϴ�.
������ ����Ʈ Ÿ�Կ� ������� 1�ʸ��� ���ŵ˴ϴ�.
FPS => Frame Per Second, �ʴ� ������ ����
*/
void FrameController::OnTrigger_RefreshFPS()
{
	// �� �� ������ ������ ���� (������ ī��Ʈ / ���� ������ �ð�)�� �̿��ϱ⵵ �ؿ�!
	//m_FPS = static_cast<Int32>(m_frameCnt / m_accumulationFrameTime);

	// ������ ������ �ƴϾ FPS�� �� ��Ȯ�ؿ�!
	m_FPS = m_frameCnt;

	m_listFPS.push_back(m_FPS);
	DEBUG_LOG_CATEGORY(FrameController, "���� ������ ī��Ʈ(%d) FPS(%d)", m_frameCnt, m_FPS);

	m_accumulationFrameTime -= FPS_UPDATE_TIME; // ¥���� �ð��� �����ҰԿ�!
	m_frameCnt = 0; // ������ ī��Ʈ�� FPS �����̹Ƿ� �ʱ�ȭ�ؾ� �ؿ�!

	// ��� FPS�� 10�� ����!
	if (m_listFPS.size() == MAX_FPS_CNT)
	{
		Int32 totalFPS = 0;
		for (auto& iter : m_listFPS)
		{
			totalFPS += iter;
		}

		m_avgFPS = totalFPS / MAX_FPS_CNT;
		DEBUG_LOG_CATEGORY(FrameController, "��� FPS(%d)", m_avgFPS);
		m_listFPS.clear();
	}
}
