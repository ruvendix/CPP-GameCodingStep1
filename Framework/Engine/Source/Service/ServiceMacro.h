// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 서비스 로케이터에게 필요한 매크로 함수 모음입니다.
// =====================================================================================
#pragma once

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