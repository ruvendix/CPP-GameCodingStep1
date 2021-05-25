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

	virtual void SetUp() override;
	virtual void CleanUp() override;

	virtual const Char* FindErrorContent(EErrorCode errorCode) const override;

	virtual EErrorCode ObtainLastError() const override
	{
		return m_lastError;
	}

	virtual void ModifyLastError(EErrorCode errorCode) override
	{
		m_lastError = errorCode;
	}

private:
	EErrorCode m_lastError = EErrorCode::UNKNOWN;
	std::unordered_map<EErrorCode, std::string> m_mapError;
};