// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 모든 서비스에 접근할 때 사용됩니다.
// 서비스 로케이터는 싱글톤으로 구현했습니다.
// =====================================================================================
#pragma once

#include "Common/CommonMacro.h"
#include "ServiceMacro.h"

class ServiceLocator final
{
	GENERATE_LOCAL_SINGLETON(ServiceLocator);

	DECLARE_SERVICE_SMARTPOINTER(IConsoleHandler, ConsoleHandler);
	DECLARE_SERVICE_SMARTPOINTER(ILogger, Logger);
	DECLARE_SERVICE_SMARTPOINTER(IErrorHandler, ErrorHandler);
	DECLARE_SERVICE_SMARTPOINTER(IGameObjectManager, GameObjectManager);
};