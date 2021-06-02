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

	std::chrono::system_clock::time_point GetStartTimePoint() const { return m_startTimePoint; }
	std::chrono::system_clock::time_point GetEndTimePoint() const { return m_startTimePoint; }

	Float GetElapsedTime() const { return m_elapsedTime; }

private:
	std::chrono::system_clock::time_point m_startTimePoint;
	std::chrono::system_clock::time_point m_endTimePoint;

	Float m_elapsedTime = 0.0f;
};