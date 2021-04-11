// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �׽�Ʈ �����Դϴ�.
// =====================================================================================
#include "pch.h"

#include "Common/CommonInclusion.h"
#include "Service/ServiceInclusion.h"

#ifdef _DEBUG
#pragma comment(lib, "Engine_Debug.lib")
#else
#pragma comment(lib, "Engine.lib")
#endif

TEST(ConsoleServiceTest, ReturnValueCheck)
{
	IConsoleHandler* pConsole = ServiceLocator::I().IConsoleHandlerInstance();
	ASSERT_NE(pConsole, nullptr);

	ASSERT_EQ(pConsole->SetUp(), EReturnType::SUCCESS);
	ASSERT_EQ(pConsole->CleanUp(), EReturnType::SUCCESS);
}