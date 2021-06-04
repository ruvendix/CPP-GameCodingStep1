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

// ���� ����
class ErrorHandlerInside;

class ErrorHandler final : public IErrorHandler
{
	ONLY_SUBSYSTEM_CTOR(ErrorHandler);

public:
	virtual void SetUp() override;
	virtual void CleanUp() override;

	virtual const Char* LastErrorString() override;

private:
	std::unique_ptr<ErrorHandlerInside> m_spInside = nullptr;
};