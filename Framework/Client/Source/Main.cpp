// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 프로그램의 진입점입니다.
// =====================================================================================

#include <EnginePCH.h>
#include <Service/GameObject/GameObject.h>

#ifdef _DEBUG
#pragma comment(lib, "Engine_Debug.lib")
#else
#pragma comment(lib, "Engine.lib")
#endif

int main()
{
	ServiceLocator::I().IConsoleHandlerInstance()->SetUp();
	ServiceLocator::I().ILoggerInstance()->SetUp();
	ServiceLocator::I().IErrorHandlerInstance()->SetUp();
	ServiceLocator::I().IGameObjectManagerInstance()->SetUp();
	ServiceLocator::I().ITimeInstance()->SetUp();

	GameObject obj;
	obj.SetUp();
	ServiceLocator::I().IGameObjectManagerInstance()->AddGameObject(&obj);

	Int32 callCount = 60 * 5; // 5초
	while (callCount != 0)
	{
		ServiceLocator::I().IGameObjectManagerInstance()->UpdateAllGameObject();

		ServiceLocator::I().IConsoleHandlerInstance()->ClearScreen();
		ServiceLocator::I().IGameObjectManagerInstance()->RenderAllGameObject();
		ServiceLocator::I().ITimeInstance()->UpdateFrameTime();

		ServiceLocator::I().IConsoleHandlerInstance()->FlipOutputBuffer();

		--callCount;
	}
	
	ServiceLocator::I().ITimeInstance()->CleanUp();
	ServiceLocator::I().IGameObjectManagerInstance()->CleanUp();
	ServiceLocator::I().IErrorHandlerInstance()->CleanUp();
	ServiceLocator::I().ILoggerInstance()->CleanUp();
	ServiceLocator::I().IConsoleHandlerInstance()->CleanUp();

	return 0;
}