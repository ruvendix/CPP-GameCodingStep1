// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �����ġ�Դϴ�.
// ���� �ð������� ��� �ð��� ����մϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "Common/CommonType.h"

class Stopwatch
{
public:
	Stopwatch();
	virtual ~Stopwatch() = default;

	void StartTime();
	void EndTime();
	void RestartTime();

	std::chrono::system_clock::time_point getStartTimePoint() const
	{
		return m_startTimePoint;
	}

	std::chrono::system_clock::time_point getEndTimePoint() const
	{
		return m_startTimePoint;
	}

	Float getElapsedTime() const
	{
		return m_elapsedTime;
	}

private:
	std::chrono::system_clock::time_point m_startTimePoint;
	std::chrono::system_clock::time_point m_endTimePoint;

	Float m_elapsedTime = 0.0f;
};