// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ܼ�â�� �ٷ�� �ڵ鷯�Դϴ�.
// =====================================================================================
#pragma once

#include "Common/Common.h"

class ConsoleHandler final
{
	DECLARE_LOCAL_SINGLETON(ConsoleHandler);

public:
	void TestFunc()
	{
		printf("�̱������� �Լ� ȣ��!\n");
	}
};