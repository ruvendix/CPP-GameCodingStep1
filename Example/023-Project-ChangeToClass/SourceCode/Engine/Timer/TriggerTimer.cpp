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

void TriggerTimer::AddDeltaTime()
{
	m_elapsedTime += FrameController::I()->getDeltaTime();
}
