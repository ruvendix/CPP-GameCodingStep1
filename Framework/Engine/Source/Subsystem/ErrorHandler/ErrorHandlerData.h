// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �ڵ鷯�� ���Ǵ� �ܺ� �������Դϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonType.h"
#include "Subsystem/SubsystemData.h"
#include "ErrorEnum.h"

class ErrorHandlerData final : public SubsystemData
{
public:
	ErrorHandlerData() = default;
	~ErrorHandlerData() = default;

	EErrorCode GetLastErrorCode() const { return m_errorCode; }
	void SetLastErrorCode(EErrorCode errorCode) { m_errorCode = errorCode; }

private:
	EErrorCode m_errorCode = EErrorCode::UNKNOWN;
};