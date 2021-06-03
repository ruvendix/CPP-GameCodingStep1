// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �ڵ鷯�� �������̽��Դϴ�.
// =====================================================================================
#pragma once

#include "Subsystem/ISubsytem.h"
#include "ErrorEnum.h"

class IErrorHandler : public ISubsystem
{
	GENERATE_SUBSYSTEM_ID(ESubsystemID::ERROR_HANLDER);

public:
	IErrorHandler() = default;
	virtual ~IErrorHandler() = default;

	virtual void SetUp() EMPTY_FUNC;
	virtual void CleanUp() EMPTY_FUNC;

	virtual const Char* FindErrorContent(EErrorCode errorCode) const PURE_FUNC;

	virtual EErrorCode ObtainLastError() const PURE_FUNC;
	virtual void ModifyLastError(EErrorCode errorCode) PURE_FUNC;
};