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

#include "Common/CommonBase.h"
#include "Common/CommonInterface.h"

#include "ErrorEnum.h"

// ���� ����
class ErrorTracerInside;

class ErrorTracer final : public ICommon
{
	GENERATE_LOCAL_SINGLETON(ErrorTracer);

public:
	virtual void StartUp() override;
	virtual void CleanUp() override;

	const Char* LastErrorString() const;

	EErrorCode GetLastErrorCode() const { return m_errorCode; }
	void SetLastErrorCode(EErrorCode errorCode) { m_errorCode = errorCode; }

private:
	ErrorTracerInside* m_pInside = nullptr;
	EErrorCode m_errorCode = EErrorCode::UNKNOWN;
};