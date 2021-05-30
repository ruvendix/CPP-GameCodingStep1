// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ð� ��ġ�Դϴ�.
// ��� �ð� ��ġ�� ���� �ð��� ���� �־�� �մϴ�.
// =====================================================================================
#include "EnginePCH.h"
#include "Stopwatch.h"

/*
	���� �ð��� ���� �ð��� �ʱ�ȭ�մϴ�.
*/
Stopwatch::Stopwatch()
{
	StartTime();
	m_endTimePoint = m_startTimePoint;
}

/*
	���� �ð��� �����մϴ�.
*/
void Stopwatch::StartTime()
{
	m_startTimePoint = std::chrono::system_clock::now();
}

/*
	���� �ð��� �����ϰ� ��� �ð��� ����մϴ�.
*/
void Stopwatch::EndTime()
{
	m_endTimePoint = std::chrono::system_clock::now();
	std::chrono::duration<Float> duration = m_endTimePoint - m_startTimePoint;
	m_elapsedTime = duration.count();
}

/*
	���� �ð��� ���� �ð��� �����ϰ� ��� �ð��� �ʱ�ȭ�մϴ�.
*/
void Stopwatch::RestartTime()
{
	m_elapsedTime = 0.0f;
	m_startTimePoint = m_endTimePoint;
}