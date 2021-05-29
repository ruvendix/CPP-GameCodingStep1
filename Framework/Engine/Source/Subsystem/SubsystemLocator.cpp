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

#include "Subsystem/Log/Logger.h"
#include "Subsystem/Error/ErrorHandler.h"
#include "Subsystem/GameObject/GameObjectManager.h"
#include "Subsystem/Time/FrameTimeManager.h"
#include "Subsystem/Console/ConsoleHandler.h"
#include "Subsystem/Console/DoubleBufferingConsoleHandler.h"

/*
	기본 서브시스템만 추가합니다.
	여기에 없는 서브시스템은 클라이언트에서 추가해주세요!
*/
void SubsystemLocator::SetUp()
{
	AddSubsystem<Logger>();
	AddSubsystem<ErrorHandler>();
	AddSubsystem<GameObjectManager>();
	AddSubsystem<FrameTimeManager>();
	AddSubsystem<DoubleBufferingConsoleHandler>();
}

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