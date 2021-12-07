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
#include <Scene/Actor/Base/ActorInclusion.h>
#include <Scene/Component/Transform.h>

Int32 main()
{
	Logger::I().StartUp();

	SubsystemLocator::I().StartUp();

	Actor* pActor = FIND_SUBSYSTEM(IActorManager)->CreateActor<Actor>();
	pActor->AddComponent<Transform>();
	Transform* pTransform = pActor->FindComponent<Transform>();
	pTransform->Print();
	SAFE_DELETE(pActor);

	SubsystemLocator::I().CleanUp();
	Logger::I().CleanUp();

	return 0;
}