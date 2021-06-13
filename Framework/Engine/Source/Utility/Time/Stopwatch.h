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

// ���� ����
class StopwatchInside;

class Stopwatch
{
public:
	Stopwatch();
	~Stopwatch();

	void StartTime();
	Float EndTime();

private:
	std::unique_ptr<StopwatchInside> m_spInside = nullptr;
};