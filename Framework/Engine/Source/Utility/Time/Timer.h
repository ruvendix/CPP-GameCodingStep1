// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Ÿ�̸��Դϴ�.
// ���� �ð����� 0�� �Ǿ������� ��Ȯ�� ����� �ϴµ� ȣ�� ������带 ���̱� ����
// ��ŸŸ���� �̿��߽��ϴ�. ��ŸŸ���� FrameManagerData�� �ֽ��ϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonType.h"

// ���� ����
class TimerInside;

class Timer
{
public:
	Timer();
	~Timer();

	Bool UpdateTime();

	void Enable() { m_bEnable = true; }
	void Disable() { m_bEnable = false; }

	void SetTargetTime(Float targetTime) { m_targetTime = targetTime; }
	void SetLoop(Bool bLoop) { m_bLoop = bLoop; }

private:
	Bool m_bEnable = true;
	Bool m_bLoop = false;

	Float m_targetTime = 0.0f;
	std::unique_ptr<TimerInside> m_spInside = nullptr;
};