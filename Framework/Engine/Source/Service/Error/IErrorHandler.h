// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �ڵ鷯�� �������̽��Դϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonInterface.h"
#include "ErrorEnum.h"

class IErrorHandler : public IService
{
public:
	IErrorHandler() = default;
	virtual ~IErrorHandler() = default;

	virtual EReturnType SetUp() { return EReturnType::SUCCESS; }
	virtual EReturnType CleanUp() { return EReturnType::SUCCESS; }

	virtual void FindErrorContent(OUT std::string& strError) = 0;
	virtual void SetLastError(EErrorType error) = 0;
};