// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ������ Ÿ�� �Ŵ����Դϴ�.
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

	// CF(���� ������)������ ������ ���� �ð���
	// ó�� ��� �ð��� �޽� �ð��� ���� ���̿���!
	spData->SetDeltaTime(elapsedTime + sleepTime);
	//RX_SIMPLE_TRACE("%f", m_deltaTime);

	m_deltaTimeStopwatch.RestartTime();

	Int32 frameRate = spData->GetFrameRate();
	spData->SetFrameRate(frameRate + 1); // ������Ʈ ~ �������� ��ĥ ������ 1�� �����մϴ�.

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
	������ ���� ������ �ʱ�ȭ�մϴ�.
*/
void ConstantFrameManager::SetUp()
{
	m_spInside->SetUp();
}

/*
	������ ���� ������ �����մϴ�.
	������ �߰��� ������ �����.
*/
void ConstantFrameManager::CleanUp()
{
	
}

/*
	������ �ð��� �����մϴ�.
	����� ���� ������ ����Ʈ�� ��� ���̹Ƿ�
	���� �ð���ŭ CPU���� �޽��� �ٰԿ�.
*/
void ConstantFrameManager::UpdateFrameTime()
{
	m_spInside->UpdateFrameTime(*this);
}