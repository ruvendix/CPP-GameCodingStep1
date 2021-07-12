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
#include <Scene/Actor/Base/ActorInclusion.h>
#include <Scene/Component/Transform.h>

Int32 main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Logger::I().SetUp();
	ErrorTracer::I().SetUp();

	SubsystemLocator::I().SetUp();

	//FIND_SUBSYSTEM(ILogger)->Data()->DeactivateOption(EnumIdx::LogOption::ABSOLUTE_FILEPATH);

	//Actor* pActor = FIND_SUBSYSTEM(IActorManager)->CreateActor<Actor>();
	//pActor->AddComponent<Component::Transfrom>();

	//FIND_SUBSYSTEM(IActorManager)->AddActor(pActor);
	//FIND_SUBSYSTEM(IActorManager)->Update();

	//Float time = 1.0f;

	//constexpr Uint32 timeUnitCount = ToUnderlyingType(EConvertionTimeUnit::COUNT);
	//const Char* times[timeUnitCount] =
	//{
	//	"밀리초", "초", "분", "시", "일", "년"
	//};

	//for (Uint32 i = 0; i < timeUnitCount; ++i)
	//{
	//	RX_TRACE("-----------------------------------------------------------------------------------------");
	//	for (Uint32 j = 0; j < timeUnitCount; ++j)
	//	{
	//		Float ret = FIND_SUBSYSTEM(ITimeHandler)->ConvertTime(
	//			time, static_cast<EConvertionTimeUnit>(i), static_cast<EConvertionTimeUnit>(j));
	//		RX_TRACE("%s -> %s: %f", times[i], times[j], ret);
	//	}

	//	RX_TRACE("");
	//	for (Uint32 j = 0; j < timeUnitCount; ++j)
	//	{
	//		Float ret = FIND_SUBSYSTEM(ITimeHandler)->ConvertTime(
	//			time, static_cast<EConvertionTimeUnit>(j), static_cast<EConvertionTimeUnit>(i));
	//		RX_TRACE("%s -> %s: %f", times[j], times[i], ret);
	//	}

	//	//Int32 a = 100;
	//}
	//RX_TRACE("-----------------------------------------------------------------------------------------");

	// 일단 시간을 찍어보자
	//std::string strLocalTime;
	//FIND_SUBSYSTEM(ITimeHandler)->MakeLocalTimeString(strLocalTime, '_');

	SubsystemLocator::I().CleanUp();

	ErrorTracer::I().CleanUp();
	Logger::I().CleanUp();

	::OutputDebugString("--------------------------------------------------------------------------\n");
	return 0;
}