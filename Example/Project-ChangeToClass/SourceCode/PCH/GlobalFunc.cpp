// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
// =====================================================================================

#include "PCH.h"
#include "GlobalFunc.h"

/*
    ���� ���α׷��� ��� ����ϴ�.
*/
void GlobalFunc::PauseGameApp()
{
	system("pause");
}

/*
    �ܼ�â�� �����ϰ� ����ϴ�.
*/
void GlobalFunc::ClearConsoleScreen()
{
	system("cls");
}

/*
	ǥ�� �Է� ���۸� ���ϴ�.
*/
void GlobalFunc::ClearStdInputBuffer()
{
	char val = '0'; // EOF�� '\n'�� �ƴϸ� �����ƿ�.

	// ǥ�� �Է� ���۸� ���� ����̿���.
	// std::fflush(stdin)�� ������, ǥ�ؿ��� �������� �ʾƼ� �����ҰԿ�.
	while ( (val != EOF) &&
		    (val != '\n') )
	{
		val = static_cast<char>(getchar());
	}
}

/*
    �ܼ� ��ǥ�� �̵���ŵ�ϴ�.
*/
void GlobalFunc::MoveConsolePos(Int32 x, Int32 y)
{
	const COORD pos{static_cast<short>(x), static_cast<short>(y)};
	::SetConsoleCursorPosition(::GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*
    ���� �ܼ� ��ǥ�� �˷��ݴϴ�.
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
    ���ڸ� �Է� ������ ���ÿ� �Է� ������ ����� ���� ������ �ڵ� �����մϴ�.
*/
bool GlobalFunc::InputNumClamp(_Out_ Int32& num, Int32 minNum, Int32 maxNum)
{
	// �ּڰ��� �ִ񰪺��� ũ�ٸ� ���� �ٲ�� �ؿ�! (swap)
	if (minNum > maxNum)
	{
		std::swap(minNum, maxNum);
	}

	printf("�Է� ������ ����� �ڵ� �����˴ϴ�. (%d ~ %d)\n", minNum, maxNum);
	printf("> ");

	Int32 inputResult = scanf_s("%d", &num);
	printf("\n");
	ClearStdInputBuffer();

	if (inputResult == 0)
	{
		printf("������ �Է� �����ؿ�!\n\n");
		return false;
	}

	num = Clamp(num, minNum, maxNum);
	return true;
}

/*
    ���ڸ� ���ѵ� ������ ������ŵ�ϴ�.
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
    ���� �ܼ� �ؽ�Ʈ ������ �˷��ݴϴ�.
*/
EConsoleTextColorType GlobalFunc::QueryCurrentConsoleTextColor()
{
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	::ZeroMemory(&consoleScreenBufferInfo, sizeof(consoleScreenBufferInfo));

	::GetConsoleScreenBufferInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &consoleScreenBufferInfo);

	if ( (consoleScreenBufferInfo.wAttributes < static_cast<INT32>(EConsoleTextColorType::BLACK)) ||
		 (consoleScreenBufferInfo.wAttributes > static_cast<INT32>(EConsoleTextColorType::BRIGHT_WHITE)) )
	{
		printf("�����Ǵ� ���� ������ �ʰ��߾��!\n");
	}

	return static_cast<EConsoleTextColorType>(consoleScreenBufferInfo.wAttributes);
}
