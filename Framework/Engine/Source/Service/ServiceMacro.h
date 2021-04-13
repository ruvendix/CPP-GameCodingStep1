// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �������Ϳ��� �ʿ��� ��ũ�� �Լ� �����Դϴ�.
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