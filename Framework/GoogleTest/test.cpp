// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 구글 테스트 예제입니다.
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