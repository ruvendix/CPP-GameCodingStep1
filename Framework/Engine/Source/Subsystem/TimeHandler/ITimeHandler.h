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
	GENERATE_SUBSYSTEM_TYPE(ESubsystemType::TIME_HANDLER);
	GENERATE_SUBSYSTEM_DATA(TimeData);

public:
	ITimeHandler() = default;
	virtual ~ITimeHandler() = default;

	virtual Uint32 ConvertSecondsToMinutes(Float seconds) const PURE_FUNC;
	virtual Uint32 ConvertSecondsToHours(Float seconds) const PURE_FUNC;

	virtual void MakeLocalTimeString(OUT std::string& strLocalTime, Char delimiter) PURE_FUNC;
};