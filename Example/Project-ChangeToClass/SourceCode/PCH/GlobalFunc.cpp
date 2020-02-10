// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include "PCH.h"
#include "GlobalFunc.h"

/*
    응용 프로그램을 잠시 멈춥니다.
*/
void GlobalFunc::PauseGameApp()
{
	system("pause");
}

/*
    콘솔창을 깨끗하게 지웁니다.
*/
void GlobalFunc::ClearConsoleScreen()
{
	system("cls");
}

/*
	표준 입력 버퍼를 비웁니다.
*/
void GlobalFunc::ClearStdInputBuffer()
{
	char val = '0'; // EOF나 '\n'만 아니면 괜찮아요.

	// 표준 입력 버퍼를 비우는 방법이에요.
	// std::fflush(stdin)도 있지만, 표준에는 적합하지 않아서 생략할게요.
	while ( (val != EOF) &&
		    (val != '\n') )
	{
		val = static_cast<char>(getchar());
	}
}

/*
    콘솔 좌표를 이동시킵니다.
*/
void GlobalFunc::MoveConsolePos(Int32 x, Int32 y)
{
	const COORD pos{static_cast<short>(x), static_cast<short>(y)};
	::SetConsoleCursorPosition(::GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*
    현재 콘솔 좌표를 알려줍니다.
*/
COORD GlobalFunc::GetCurrentConsolePos()
{
	COORD pos{0, 0};
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	::ZeroMemory(&consoleScreenBufferInfo, sizeof(consoleScreenBufferInfo));

	::GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleScreenBufferInfo);
	pos.X = consoleScreenBufferInfo.dwCursorPosition.X;
	pos.Y = consoleScreenBufferInfo.dwCursorPosition.Y;

	return pos;
}

/*
    숫자를 입력 받음과 동시에 입력 범위를 벗어나면 범위 안으로 자동 조절합니다.
*/
bool GlobalFunc::InputNumClamp(_Out_ Int32& num, Int32 minNum, Int32 maxNum)
{
	// 최솟값이 최댓값보다 크다면 둘을 바꿔야 해요! (swap)
	if (minNum > maxNum)
	{
		std::swap(minNum, maxNum);
	}

	printf("입력 범위를 벗어나면 자동 조절됩니다. (%d ~ %d)\n", minNum, maxNum);
	printf("> ");

	Int32 inputResult = scanf_s("%d", &num);
	printf("\n");
	ClearStdInputBuffer();

	if (inputResult == 0)
	{
		printf("정수만 입력 가능해요!\n\n");
		return false;
	}

	num = Clamp(num, minNum, maxNum);
	return true;
}

/*
    숫자를 제한된 범위로 고정시킵니다.
*/
Int32 GlobalFunc::Clamp(Int32 val, Int32 minVal, Int32 maxVal)
{
	Int32 resultVal = val;

	if (resultVal < minVal)
	{
		resultVal = minVal;
	}
	else if (resultVal > maxVal)
	{
		resultVal = maxVal;
	}

	return resultVal;
}

/*
    현재 콘솔 텍스트 색상을 알려줍니다.
*/
EConsoleTextColorType GlobalFunc::QueryCurrentConsoleTextColor()
{
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	::ZeroMemory(&consoleScreenBufferInfo, sizeof(consoleScreenBufferInfo));

	::GetConsoleScreenBufferInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &consoleScreenBufferInfo);

	if ( (consoleScreenBufferInfo.wAttributes < static_cast<INT32>(EConsoleTextColorType::BLACK)) ||
		 (consoleScreenBufferInfo.wAttributes > static_cast<INT32>(EConsoleTextColorType::BRIGHT_WHITE)) )
	{
		printf("제공되는 색상 범위를 초과했어요!\n");
	}

	return static_cast<EConsoleTextColorType>(consoleScreenBufferInfo.wAttributes);
}
