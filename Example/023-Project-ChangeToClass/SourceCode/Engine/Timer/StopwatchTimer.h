// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ð� ������ ������ Ÿ�̸��Դϴ�. (�����ġ)
// ���� �ð��� ���� �ð� �� �� �����մϴ�.
// =====================================================================================

#ifndef STOPWATCH_TIMER__H__
#define STOPWATCH_TIMER__H__

#include "Common\CommonType.h"
#include "Common\CommonMacro.h"
#include "Common\CommonNecessary.h"

class StopwatchTimer final
{
public:
#pragma region ������ �� �Ҹ���
	StopwatchTimer() = default;
	~StopwatchTimer() = default;
#pragma endregion

	void StartTime();
	Real32 EndTime();

private:
	Uint32 m_startTime = 0;
	Uint32 m_endTime = 0;
};

#endif