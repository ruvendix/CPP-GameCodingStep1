// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �������� �߻��� ������ �ش�Ǵ� ������ �˷��ݴϴ�.
// ������ �߻����ڸ��� ���� �ڵ鷯�� �۵��˴ϴ�.
// =====================================================================================
#pragma once

#include "IErrorHandler.h"

class ErrorHandler : public IErrorHandler
{
public:
	ErrorHandler() = default;
	virtual ~ErrorHandler() = default;

	virtual EReturnType SetUp() override;
	virtual EReturnType CleanUp() override;

	virtual void FindErrorContent(OUT std::string& strError) override;
	virtual void SetLastError(EErrorType error) override;

private:
	EErrorType m_lastError = EErrorType::NONE;
	std::unordered_map<EErrorType, std::string> m_mapError;
};