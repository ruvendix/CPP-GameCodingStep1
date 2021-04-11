// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 프로그램의 진입점입니다.
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
	pConsole->RenderText(0, 0, "흐음");

	pConsole->CleanUp();
	return 0;
}