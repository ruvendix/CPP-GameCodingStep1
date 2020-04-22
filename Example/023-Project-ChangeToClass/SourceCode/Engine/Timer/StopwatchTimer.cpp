// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ð� ������ ������ Ÿ�̸��Դϴ�. (�����ġ)
// ���� �ð��� ���� �ð� �� �� �����մϴ�.
// =====================================================================================

#include "PCH.h"
#include "StopwatchTimer.h"

/*
���� �ð��� �����մϴ�.
*/
void StopwatchTimer::StartTime()
{
	m_startTime = std::chrono::system_clock::now();
}

/*
���� �ð��� �����մϴ�.
��� �ð��� ����ؼ� �����մϴ�.
*/
void StopwatchTimer::EndTime()
{
	m_endTime = std::chrono::system_clock::now();

	std::chrono::duration<Real32> elaspedTime = m_endTime - m_startTime; // �⺻ ������ ��!
	//DEBUG_LOG("�ð� ���� : (%f)��", timeInterval.count());
	m_elaspedTime = elaspedTime.count();
}