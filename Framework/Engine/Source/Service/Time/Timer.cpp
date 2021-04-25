// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Ÿ�̸��Դϴ�.
// ��ǥ �ð������� ��� �ð��� ��Ȯ�� ����� �ϹǷ� ��ŸŸ���� �̿��մϴ�.
// ��ŸŸ���� Time Ŭ������ �ֽ��ϴ�. (�̸��� ����ϴϱ� ����!)
// =====================================================================================
#include "EnginePCH.h"
#include "Timer.h"

#include "Time.h"

/*
	��ŸŸ���� �����ϸ鼭 ��ǥ �ð����� �޼��ߴ��� Ȯ���մϴ�.
	��ǥ �ð����� �޼������� true��, �ƴ϶�� false�� ��ȯ�մϴ�.
*/
Bool Timer::UpdateTime()
{
	if (m_bEnable == false)
	{
		return false;
	}

	m_localTime += ServiceLocator::I().ITimeInstance()->GetDeltaTime();
	ServiceLocator::I().IConsoleHandlerInstance()->RenderString(0, 1, MakeFormatString("localTime: %f", m_localTime).c_str());

	if (m_targetTime > m_localTime)
	{
		return false;
	}

	m_localTime = 0.0f;

	if (m_bLoop == false)
	{
		m_bEnable = false;
	}

	return true;
}