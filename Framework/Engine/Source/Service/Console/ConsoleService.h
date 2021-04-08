// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ܼ� �����Դϴ�.
// �ܼ�â�� �ٷ� �� ���˴ϴ�.
// =====================================================================================
#pragma once

#include "Common/Common.h"
#include "IConsoleService.h"

class ConsoleService final : public IConsoleService
{
public:
	ConsoleService() = default;
	virtual ~ConsoleService() = default;

	virtual void TestFunc() override
	{
		printf("���� �������ͷ� �ܼ� ������ �Լ� ȣ��!\n");
	}
};

class ConsoleService_Version2 final : public IConsoleService
{
public:
	ConsoleService_Version2() = default;
	virtual ~ConsoleService_Version2() = default;

	virtual void TestFunc() override
	{
		printf("���� �������ͷ� �ܼ� ���� ����2�� �Լ� ȣ��!\n");
	}
};