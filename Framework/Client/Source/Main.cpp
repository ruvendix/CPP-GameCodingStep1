// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���α׷��� �������Դϴ�.
// =====================================================================================

#ifdef _DEBUG
#pragma comment(lib, "Engine_Debug.lib")
#else
#pragma comment(lib, "Engine.lib")
#endif

#include <EnginePCH.h>
#include <Subsystem/GameObject/GameObject.h>

int main()
{
	SubsystemLocator::I().SetUp();

	FIND_SUBSYSTEM(IConsoleHandler)->SetUp();
	FIND_SUBSYSTEM(ILogger)->SetUp();
	FIND_SUBSYSTEM(IErrorHandler)->SetUp();
	FIND_SUBSYSTEM(IGameObjectManager)->SetUp();
	FIND_SUBSYSTEM(IFrameTimeManager)->SetUp();

	GameObject obj;
	obj.SetUp();
	FIND_SUBSYSTEM(IGameObjectManager)->AddGameObject(&obj);

	Int32 callCount = 60 * 5; // 5��
	while (callCount != 0)
	{
		FIND_SUBSYSTEM(IGameObjectManager)->UpdateAllGameObject();

		FIND_SUBSYSTEM(IConsoleHandler)->ClearScreen();
		FIND_SUBSYSTEM(IGameObjectManager)->RenderAllGameObject();
		FIND_SUBSYSTEM(IFrameTimeManager)->UpdateFrameTime();

		FIND_SUBSYSTEM(IConsoleHandler)->FlipOutputBuffer();

		--callCount;
	}

	SubsystemLocator::I().CleanUp();
	return 0;
}