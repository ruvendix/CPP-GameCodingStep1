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
	IConsoleHandler* pConsole = ServiceLocator::I().IConsoleHandlerInstance();
	pConsole->SetUp();

	pConsole->ShowCursor(false);

	pConsole->ChangeRenderColor(EConsoleRenderingColor::AQUA, EConsoleRenderingType::BACKGROUND);

	const Char* sz = pConsole->InputString();
	Int32 value1 = pConsole->InputInteger();
	Float value2 = pConsole->InputFloat();

	pConsole->RenderText(10, 10, sz);
	pConsole->MovePosition(0, 0);

	pConsole->ClearScreen();
	pConsole->ChangeRenderColor(EConsoleRenderingColor::RED, EConsoleRenderingType::TEXT);
	pConsole->RenderText(0, 0, "����");

	pConsole->CleanUp();
	return 0;
}