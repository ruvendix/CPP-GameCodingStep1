// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������ �ð����� �̺�Ʈ�� �߻��ϴ� Ÿ�̸��Դϴ�.
// �ݺ����� �����Ǿ������� �̺�Ʈ�� �ֱ������� �߻��մϴ�.
// �ܵ����� ���� ���� ���� �Ŵ����� �̿��ؾ� �մϴ�.
// =====================================================================================

#include "PCH.h"
#include "TriggerTimer.h"

#include "Controller\FrameController.h"

/*
��� �ð��� �ð� ������ ���մϴ�.
���� �ð��� �ƴ϶� ���� �ð���ŭ ���ؾ� �մϴ�.
*/
void TriggerTimer::AddElapsedTime()
{
	EndTime();
	m_triggerElaspedTime += getElaspedTime();
	SwapTime();

	//DEBUG_LOG("(%f)�� üũ!", m_elapsedTime);

	//m_elapsedTime += FrameController::I()->getDeltaTime();
	//static Int32 cnt = 0;
	//DEBUG_LOG("%f�� üũ! (%f) (%d)", m_elapsedTime, FrameController::I()->getDeltaTime(), ++cnt);
}

void TriggerTimer::UpdateKeepTime()
{
	m_keepTime -= FrameController::I()->getDeltaTime();
}
