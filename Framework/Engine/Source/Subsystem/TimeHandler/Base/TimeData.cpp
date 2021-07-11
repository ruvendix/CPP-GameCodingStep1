// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Ÿ�� �ڵ鷯�� ���Ǵ� �ܺ� �������Դϴ�.
// =====================================================================================
#pragma once

#include "EnginePCH.h"
#include "TimeData.h"

TimeData::TimeData()
{
	for (Int32 i = 0; i < EnumIdx::TimeUnit::COUNT; ++i)
	{
		m_timeUnits.set(false);
		m_timeOrders[i] = EnumIdx::TimeUnit::UNKNOWN;
	}
}