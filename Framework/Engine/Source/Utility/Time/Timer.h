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
#pragma once

#include "Common/CommonType.h"

class Timer
{
public:
	Timer() = default;
	virtual ~Timer() = default;

	Bool UpdateTime();

	void Enable()
	{
		m_bEnable = true;
	}

	void Disable()
	{
		m_bEnable = false;
	}

	void setTargetTime(Float targetTime)
	{
		m_targetTime = targetTime;
	}

	void setLoop(Bool bLoop)
	{
		m_bLoop = bLoop;
	}

private:
	Bool m_bEnable = true;
	Bool m_bLoop = false;

	Float m_localTime = 0.0f;
	Float m_targetTime = 0.0f;
};