// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 프로그램의 진입점입니다.
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