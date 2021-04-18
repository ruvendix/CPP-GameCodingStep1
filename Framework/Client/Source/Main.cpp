// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���α׷��� �������Դϴ�.
// =====================================================================================

#include <EnginePCH.h>

#ifdef _DEBUG
#pragma comment(lib, "Engine_Debug.lib")
#else
#pragma comment(lib, "Engine.lib")
#endif

int main()
{
	ServiceLocator::I().IConsoleHandlerInstance()->SetUp();
	ServiceLocator::I().ILoggerInstance()->SetUp();
	ServiceLocator::I().IErrorHandlerInstance()->SetUp();

	CEHCK_NULLPTR(nullptr);
	
	ServiceLocator::I().IErrorHandlerInstance()->CleanUp();
	ServiceLocator::I().ILoggerInstance()->CleanUp();
	ServiceLocator::I().IConsoleHandlerInstance()->CleanUp();	

	return 0;
}