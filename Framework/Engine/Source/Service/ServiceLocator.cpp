// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� ���񽺿� ������ �� ���˴ϴ�.
// ���� �������ʹ� �̱������� �����߽��ϴ�.
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