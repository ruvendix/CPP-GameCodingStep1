// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �����Ӱ� ���õ� �ð��� �ٷ�ϴ�.
// =====================================================================================
#include "EnginePCH.h"
#include "FrameTimeManager.h"

/*
	������ ���� ������ �ʱ�ȭ�մϴ�.
*/
void FrameTimeManager::SetUp()
{
	m_FPSTimer.setLoop(true);
	m_FPSTimer.setTargetTime(1.0f);

	m_deltaTimeStopwatch.StartTime();
	ModifyFixedDeltaTime(60);
}

/*
	������ ���� ������ �����մϴ�.
	������ �߰��� ������ �����.
*/
void FrameTimeManager::CleanUp()
{
	
}

/*
	������ �ð��� �����մϴ�.
	����� ���� ������ ����Ʈ�� ��� ���̹Ƿ�
	���� �ð���ŭ CPU���� �޽��� �ٰԿ�.
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

	// ���� �����Ӱ� ���� ������ ������ �ð���
	// ó�� ��� �ð��� �޽� �ð��� ���� ���̿���!
	m_deltaTime = elapsedTime + sleepTime;
	//RX_SIMPLE_TRACE("%f", m_deltaTime);
	
	m_deltaTimeStopwatch.RestartTime();
	++m_frameCount; // ������Ʈ ~ �������� ��ĥ ������ 1�� �����մϴ�.

	// Ÿ�̸Ӵ� ��ŸŸ���� ����ϰ�, Ÿ�ӿ����� Ÿ�̸Ӹ� ����մϴ�.
	// �̷��� ���� ���̴� �� ���� ������ �ƴ����� ��ŸŸ���� �ʱ갪�� 0�̶� ������ �����.
	// �ǵ����̸� �̷� ������ ������ �ʴ� �� ��õ�մϴ�!
	if (m_FPSTimer.UpdateTime() == true)
	{
		//RX_SIMPLE_TRACE("%d", m_frameCount);
		m_frameCount = 0;
	}
}