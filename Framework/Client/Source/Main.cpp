// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���α׷��� �������Դϴ�.
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

	Int32 callCount = 60 * 5; // 5��
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