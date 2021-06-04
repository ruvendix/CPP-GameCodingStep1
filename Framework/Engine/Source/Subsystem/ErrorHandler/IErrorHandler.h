// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �ڵ鷯�� �������̽��Դϴ�.
// �ܺ� �����Ϳ� �Լ��� ���� ������ �߻� Ŭ�����̱⵵ �մϴ�.
// =====================================================================================
#pragma once

#include "Subsystem/ISubsytem.h"
#include "ErrorHandlerData.h"

class IErrorHandler : public ISubsystem
{
	GENERATE_SUBSYSTEM_TYPE(ESubsystemType::ERROR_HANLDER);
	GENERATE_SUBSYSTEM_DATA(ErrorHandlerData);

public:
	IErrorHandler() = default;
	virtual ~IErrorHandler() = default;

	virtual void SetUp() EMPTY_FUNC;
	virtual void CleanUp() EMPTY_FUNC;

	virtual const Char* LastErrorString() PURE_FUNC;
};