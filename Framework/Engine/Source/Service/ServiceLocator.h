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