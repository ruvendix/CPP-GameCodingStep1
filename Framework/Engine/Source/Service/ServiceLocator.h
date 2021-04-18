// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� ���񽺿� ������ �� ���˴ϴ�.
// ���� �������ʹ� �̱������� �����߽��ϴ�.
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