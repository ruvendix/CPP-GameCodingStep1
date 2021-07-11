// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Ÿ�� �ڵ鷯�� �������̽��Դϴ�.
// �ܺ� �����Ϳ� �Լ��� ���� ������ �߻� Ŭ�����̱⵵ �մϴ�.
// =====================================================================================
#pragma once

#include "Subsystem/ISubsytem.h"
#include "TimeData.h"

class ITimeHandler : public ISubsystem
{
	GENERATE_SUBSYSTEM(ESubsystemType::TIME_HANDLER);
	GENERATE_SUBSYSTEM_DATA(TimeData);

public:
	ITimeHandler() = default;
	virtual ~ITimeHandler() = default;

	virtual Float ConvertTime(Float time, EConvertionTimeUnit src, EConvertionTimeUnit dest) CONST_PURE_FUNC;
	virtual void MakeLocalTimeString(OUT std::string& strLocalTime, Char delimiter) PURE_FUNC;

	virtual void ActivateTimeUnit(EnumIdx::TimeUnit::Data timeUnit) PURE_FUNC;
	virtual void DeactivateTimeUnit(EnumIdx::TimeUnit::Data timeUnit) PURE_FUNC;
	virtual bool CheckTimeUnit(EnumIdx::TimeUnit::Data timeUnit) CONST_PURE_FUNC;

	virtual void ChangeTimeOrder(EnumIdx::TimeUnit::Data timeUnit, Uint32 orderIdx) PURE_FUNC;
};