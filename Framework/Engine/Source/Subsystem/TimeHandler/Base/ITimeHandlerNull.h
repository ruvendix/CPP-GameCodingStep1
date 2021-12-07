// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ����� ���� Ÿ�� �ڵ鷯�Դϴ�.
// Ÿ�� �ڵ鷯�� �ʱ�ȭ���� �ʾ��� �� ���˴ϴ�.
// FIND_SUBSYSTEM() ��ũ�θ� ���ؼ��� ���˴ϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "ITimeHandler.h"

class ITimeHandlerNull : public ITimeHandler
{
public:
	virtual void StartUp() OVERRIDE_EMPTY_FUNC;
	virtual void CleanUp() OVERRIDE_EMPTY_FUNC;

	virtual Float ConvertTime(Float time, EConvertionTimeUnit src, EConvertionTimeUnit dest) CONST_OVERRIDE_RETURN_FUNC(0.0f);
	virtual void MakeLocalTimeString(std::string& strLocalTime, Char delimiter) OVERRIDE_EMPTY_FUNC;

	virtual void ActivateTimeUnit(EnumIdx::TimeUnit::Data timeUnit) OVERRIDE_EMPTY_FUNC;
	virtual void DeactivateTimeUnit(EnumIdx::TimeUnit::Data timeUnit) OVERRIDE_EMPTY_FUNC;
	virtual bool CheckTimeUnit(EnumIdx::TimeUnit::Data timeUnit) CONST_OVERRIDE_RETURN_FUNC(true);

	virtual void ChangeTimeOrder(EnumIdx::TimeUnit::Data timeUnit, Uint32 orderIdx) OVERRIDE_EMPTY_FUNC;
};