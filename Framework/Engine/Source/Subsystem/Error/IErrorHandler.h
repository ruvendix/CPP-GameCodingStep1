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
	GENERATE_MATCH_TYPE(ESubsystemType::ERROR_HANLDER)

public:
	IErrorHandler() = default;
	virtual ~IErrorHandler() = default;

	virtual void SetUp() {  }
	virtual void CleanUp() {  }

	virtual void FindErrorContent(OUT std::string& strError) = 0;
	virtual void SetLastError(EErrorType error) = 0;
};