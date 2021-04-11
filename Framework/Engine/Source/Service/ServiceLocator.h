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

#define DECLARE_SERVICE(AbstractService, ConcreteService)\
public:\
	class AbstractService* AbstractService##Instance();\
	void CleanUp##AbstractService();\
\
private:\
	class AbstractService* m_p##AbstractService = nullptr;

#define DECLARE_SERVICE_SMARTPOINTER(AbstractService, ConcreteService)\
public:\
	class AbstractService* AbstractService##Instance();\
\
private:\
	std::unique_ptr<class AbstractService> m_sp##AbstractService;

class ServiceLocator final
{
	GENERATE_LOCAL_SINGLETON(ServiceLocator);

	//DECLARE_SERVICE(IConsoleService, ConsoleService);
	DECLARE_SERVICE_SMARTPOINTER(IConsoleService, ConsoleService);
};