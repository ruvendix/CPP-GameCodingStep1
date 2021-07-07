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
#include <Scene/GameObject/GameObject.h>

#include <Scene/Actor/ActorInclusion.h>
#include <Scene/Component/Transform.h>

#include <iostream>

Int32 main()
{
	SubsystemLocator::I().SetUp();

	Actor* pActor = FIND_SUBSYSTEM(IActorManager)->CreateActor<Actor>();
	pActor->AddComponent<Component::Transfrom>();

	FIND_SUBSYSTEM(IActorManager)->AddActor(pActor);
	FIND_SUBSYSTEM(IActorManager)->Update();

	SubsystemLocator::I().CleanUp();
	return 0;
}