// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Ÿ�� �ڵ鷯�Դϴ�.
// �ð� ��ȯ �� �ð� ���� ������ �ٷ�ϴ�.
// =====================================================================================
#pragma once

#include "Base/ITimeHandler.h"

class TimeHandler : public ITimeHandler
{
	ONLY_SUBSYSTEM_CTOR(TimeHandler);

public:
	virtual void SetUp() override;
	virtual void CleanUp() override;

	virtual Float ConvertTime(Float time, EConvertionTimeUnit src, EConvertionTimeUnit dest) const override;
	virtual void MakeLocalTimeString(OUT std::string& strLocalTime, Char delimiter) override;

	virtual void ActivateTimeUnit(EnumIdx::TimeUnit::Data timeUnit) override;
	virtual void DeactivateTimeUnit(EnumIdx::TimeUnit::Data timeUnit) override;
	virtual bool CheckTimeUnit(EnumIdx::TimeUnit::Data timeUnit) const override;

	virtual void ChangeTimeOrder(EnumIdx::TimeUnit::Data timeUnit, Uint32 orderIdx) override;

private:
	using ConvertionTimeTable = std::array<Float, ToUnderlyingType(EConvertionTimeUnit::COUNT) - 1>;

	static const ConvertionTimeTable UPPER_CONVERTION_TIME_TABLE;
	static const ConvertionTimeTable LOWER_CONVERTION_TIME_TABLE;
};