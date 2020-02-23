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
���ػ� Ÿ�̸Ӹ� �̿��ؼ� ��ŸŸ���� �����մϴ�.
CPU ƽ�� �����ϹǷ� ��Ƽ�����忡���� ��Ȯ���� ���� ���� �ִٰ� �մϴ�.
���� : http://www.tipssoft.com/bulletin/board.php?bo_table=FAQ&wr_id=735
*/
void FrameControllerHelper::UpdateDeltaTime()
{
	// ���� ������ CPU ƽ�� �˾Ƴ��� �ؿ�!
	LARGE_INTEGER currentTick;
	::QueryPerformanceCounter(&currentTick);

	LARGE_INTEGER CPUFrequency = FrameController::I()->m_CPUFrequency;
	LARGE_INTEGER& prevTick = FrameController::I()->m_prevTick;
	Real32& deltaTime = FrameController::I()->m_deltaTime;

	// �ʴ����� ��ŸŸ���� ����մϴ�. (����� 2.352��� 2.352�ʶ�� �ǹ�)
	// (���� ������ CPU ƽ - ���� ������ CPU ƽ)�� ���ļ��� �����ָ� �˴ϴ�.
	deltaTime = static_cast<Real32>(currentTick.QuadPart - prevTick.QuadPart) / (CPUFrequency.QuadPart);
	//DEBUG_LOG_CATEGORY(FrameController, "��ŸŸ��(%f)", deltaTime);

	EFrameRateType frameRateType = FrameController::I()->getFrameRateType();

	// ���� ������ ����Ʈ�� ���� ������ ����Ʈ�� ������ �ɷ��ִٸ� �׸�ŭ CPU�� �����ؾ� �ؿ�!
	if ( (deltaTime < m_limitedDeltaTime) && 
		 (frameRateType != EFrameRateType::VARIABLE_UNLIMITED) )
	{
		// ���� ������ ���ݸ�ŭ CPU�� �����մϴ�.
		// ��, ���α׷� �ӵ��� ������ ��ġ���� CPU �������� ���ҵ˴ϴ�.
		Uint32 sleepTime = static_cast<Uint32>((m_limitedDeltaTime - deltaTime) * 1000.0f);
		//DEBUG_LOG_CATEGORY(FrameController,
		//	"������ ����Ʈ���� ���� �ɸ���! ������ ����Ʈ(%s) ��ŸŸ��(%f) ������ Ÿ��(%f)",
		//	(frameRateType == EFrameRateType::CONSTANT) ? ("����") : ("����"), deltaTime, static_cast<Real32>(sleepTime) * 0.001f);
		::SleepEx(sleepTime, TRUE);

		// ���� ������ ����Ʈ������ �������� ���� ��ŸŸ���� �����մϴ�.
		// ��, ��ŸŸ���� ������ ���Ѱ����� ���� �� ������ ������ ���Ѱ����� ���� ���� �־��!
		// ������ ���ݸ�ŭ ���� �� �������ϹǷ� �������� Ƣ�� ��ó�� ���� �� ����...
		if (frameRateType == EFrameRateType::VARIABLE_LIMITED)
		{
			deltaTime = m_limitedDeltaTime;
		}
	}
	
	// ���� ������ ����Ʈ������ ������ ������� ��ŸŸ���� �����˴ϴ�.
	// ��, ��ǻ�� ��翡 ������� ��ŸŸ���� �����ϹǷ� ��ǻ�͸��� ������ ���� �� ������ ���°� �ٸ� �� �ֽ��ϴ�.
	// � ��ǻ�ʹ� ���� ����Ǿ �÷����ϰ� �ִµ� � ��ǻ�ʹ� ���� ���� ������ �÷����ϴ� ��Ȳ�� �߻��� �� ����...
	if (frameRateType == EFrameRateType::CONSTANT)
	{
		deltaTime = m_limitedDeltaTime;
	}

	// �ʴ��� �������� ���� ����մϴ�.
	//Real32 milliDeltaTime = deltaTime;
	//Real32 microDeltaTime = milliDeltaTime * 0.001f;
	//Real32 nanoDeltaTime  = microDeltaTime * 0.001f;
	//DEBUG_LOG_CATEGORY(FrameController, "MilliDeltaTime(%f) MicroDeltaTime(%f) NanoDeltaTime(%f)",
	//	milliDeltaTime, microDeltaTime, nanoDeltaTime);

	prevTick = currentTick;
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_SINGLETON(FrameController);
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
}

/*
������ FPS�� ��ŸŸ���� �����մϴ�.
FPS�� ������ ��ŸŸ�Ӱ� ������ ī��Ʈ�� �̿��ؼ� �����մϴ�.
*/
void FrameController::UpdateFPSAndDeltatime()
{
	FrameControllerHelper::UpdateDeltaTime();

	m_accumulationFrameTime += m_deltaTime;
	++m_frameCnt;
	//DEBUG_LOG_CATEGORY(FrameController, "������ ī��Ʈ(%d), ��ŸŸ��(%f)", m_frameCnt, m_deltaTime);

	// 1�ʰ� �Ѿ�� FPS ����
	if (m_accumulationFrameTime >= FPS_UPDATE_TIME)
	{
		// FPS = ������ ī��Ʈ / 1��
		// �� �� ������ ������ ���� (������ ī��Ʈ / ���� ������ �ð�)�� �̿��մϴ�.
		m_FPS = static_cast<Int32>(m_frameCnt / m_accumulationFrameTime);
		m_listFPS.push_back(m_FPS);
		DEBUG_LOG_CATEGORY(FrameController, "���� ������ ī��Ʈ(%d) FPS(%d)", m_frameCnt, m_FPS);

		m_accumulationFrameTime -= FPS_UPDATE_TIME; // ¥���� �ð��� �����ҰԿ�!
		m_frameCnt = 0; // ������ ī��Ʈ�� FPS �����̹Ƿ� �ʱ�ȭ�ؾ� �ؿ�!
	}

	// ��� FPS�� 10�� �����Դϴ�.
	if (m_listFPS.size() == MAX_LIST_FPS)
	{
		Int32 totalFPS = 0;
		for (auto& iter : m_listFPS)
		{
			totalFPS += iter;
		}
		
		DEBUG_LOG_CATEGORY(FrameController, "��� FPS(%d)", totalFPS / MAX_LIST_FPS);
		m_listFPS.clear();
	}
}

/*
���ѵ� �����Ӱ��� �����մϴ�.
*/
void FrameController::ModifyLimitedFrame(Int32 limitedFrame)
{
	if (m_frameRateType == EFrameRateType::VARIABLE_UNLIMITED)
	{
		DEBUG_LOG_CATEGORY(FrameController, "������ �������̹Ƿ� ���� ������ �� �� �����!");
		return;
	}

	m_limitedFrame = limitedFrame;
	FrameControllerHelper::RefreshLimitedDeltaTime();
}