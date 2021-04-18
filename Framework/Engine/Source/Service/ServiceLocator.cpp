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
#include "ServiceLocator.h"

#include "Console/ConsoleHandler.h"
#include "Log/Logger.h"
#include "Error/ErrorHandler.h"

#define DEFINE_SERVICE(AbstractService, ConcreteService)\
	AbstractService* ServiceLocator::AbstractService##Instance()\
	{\
		if (m_p##AbstractService == nullptr)\
		{\
			m_p##AbstractService = new ConcreteService;\
		}\
\
		return m_p##AbstractService;\
	}\
\
	void ServiceLocator::CleanUp##AbstractService()\
	{\
		SAFE_DELETE(m_p##AbstractService);\
	}

#define DEFINE_SERVICE_SMARTPOINTER(AbstractService, ConcreteService)\
	AbstractService* ServiceLocator::AbstractService##Instance()\
	{\
		if (m_sp##AbstractService == nullptr)\
		{\
			m_sp##AbstractService = std::make_unique<ConcreteService>();\
		}\
\
		return m_sp##AbstractService.get();\
	}

DEFINE_SERVICE_SMARTPOINTER(IConsoleHandler, ConsoleHandler);
DEFINE_SERVICE_SMARTPOINTER(ILogger, Logger);
DEFINE_SERVICE_SMARTPOINTER(IErrorHandler, ErrorHandler);
DEFINE_SERVICE_SMARTPOINTER(IGameObjectManager, GameObjectManager);