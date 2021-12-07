// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 모든 서비스에 접근할 때 사용됩니다.
// 서비스 로케이터는 싱글톤으로 구현했습니다.
// =====================================================================================
#include "EnginePCH.h"
#include "SubsystemLocator.h"

#include "SubsystemInclusion.h"

/*
	기본 서브시스템만 등록합니다.
	여기에 없는 서브시스템은 클라이언트에서 추가해주세요!
	몇몇 서브시스템은 복잡하게 꼬여있지만 초기화되지 않은 서브시스템이라면
	널서브시스템을 이용하므로 문제는 없습니다.
*/
void SubsystemLocator::StartUp()
{
	RegisterSubsystem<TimeHandler>();
	Logger::I().SetTimeHandler(FIND_SUBSYSTEM(ITimeHandler));

	RegisterSubsystem<PathManager>();
	Logger::I().SetPathManager(FIND_SUBSYSTEM(IPathManager));

	RegisterSubsystem<ConsoleHandler>();
	//RegisterSubsystem<DoubleBufferingConsoleHandler>();
	Logger::I().SetConsoleHandler(FIND_SUBSYSTEM(IConsoleHandler));

	RegisterSubsystem<FileHandler>();
	Logger::I().SetFileHandler(FIND_SUBSYSTEM(IFileHandler));

	RegisterSubsystem<ConstantFrameManager>();
	RegisterSubsystem<ActorManager>();
}

/*
	등록된 모든 서브시스템의 CleanUp()을 호출합니다.
*/
void SubsystemLocator::CleanUp()
{
	for (auto& iter : m_mapSubsystem)
	{
		if (iter.second == nullptr)
		{
			continue;
		}

		iter.second->CleanUp();
		SAFE_DELETE(iter.second);
	}	
}