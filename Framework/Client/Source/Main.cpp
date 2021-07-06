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

Int32 main()
{
	SubsystemLocator::I().SetUp();

	FIND_SUBSYSTEM(IConsoleHandler)->AdjustSize(120, 20);
	FIND_SUBSYSTEM(ILogger)->Data()->DeactivateOption(EnumIdx::LogOption::TIME);
	FIND_SUBSYSTEM(ILogger)->Data()->DeactivateOption(EnumIdx::LogOption::LINE);
	FIND_SUBSYSTEM(ILogger)->Data()->DeactivateOption(EnumIdx::LogOption::ABSOLUTE_FILEPATH);
	FIND_SUBSYSTEM(ILogger)->Data()->DeactivateOption(EnumIdx::LogOption::RELATIVE_FILEPATH);

	std::string frameworkAbsolutePath = FIND_SUBSYSTEM(IPathManager)->FrameworkAbsolutePath();
	std::string frameworkRelativePath = FIND_SUBSYSTEM(IPathManager)->FrameworkRelativePath();
	std::string clientAbsolutePath = FIND_SUBSYSTEM(IPathManager)->ClientAbsolutePath();
	std::string clientRelativePath = FIND_SUBSYSTEM(IPathManager)->ClientRelativePath();

	RX_INFO("프레임워크 절대경로: %s", frameworkAbsolutePath.c_str());
	RX_INFO("프레임워크 상대경로: %s", frameworkRelativePath.c_str());
	RX_INFO("클라이언트 절대경로: %s", clientAbsolutePath.c_str());
	RX_INFO("클라이언트 상대경로: %s", clientRelativePath.c_str());

	SubsystemLocator::I().CleanUp();
	return 0;
}