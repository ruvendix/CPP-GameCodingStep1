// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �������� ���Ǵ� �Լ� ���� �����Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "CommonFunc.h"

/*
�ܼ� ������ �����մϴ�.
*/
void CommonFunc::AdjustConsoleArea(Int32 width, Int32 height)
{
	std::string strConsoleProperty = MakeFormatString("mode con cols=%d lines=%d", width, height);
	system(strConsoleProperty.c_str());
}

/*
SizeInfo �����ε��Դϴ�.
*/
void CommonFunc::AdjustConsoleArea(const SizeInfo& sizeInfo)
{
	AdjustConsoleArea(sizeInfo.width, sizeInfo.height);
}

/*
���ӿ� �ܼ� ��Ÿ�Ϸ� �����մϴ�.
�ִ�ȭ, �ּ�ȭ, �ݱ� ��ư�� ���� ������ �����˴ϴ�.
*/
void CommonFunc::GameConsoleStyle()
{
	HWND hConsoleWnd = ::GetConsoleWindow();
	DWORD style = ::GetWindowLong(hConsoleWnd, GWL_STYLE);
	style &= ~(WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME); // WS_MAXIMIZEBOX�� WS_THICKFRAME ���ܽ�Ű��
	::SetWindowLong(hConsoleWnd, GWL_STYLE, style);

	// �ݱ� ��ư�� ��Ȱ���ϴ� ���
	HMENU hSysMenu = ::GetSystemMenu(hConsoleWnd, FALSE);
	::DeleteMenu(hSysMenu, SC_CLOSE, MF_BYCOMMAND);
}

/*
���� ���α׷��� ��� ����ϴ�.
*/
void CommonFunc::PauseGameApp()
{
	system("pause");
}

/*
�ܼ�â�� �����ϰ� ����ϴ�.
���� : https://docs.microsoft.com/en-us/windows/console/clearing-the-screen
*/
void CommonFunc::ClearConsoleScreen()
{
#if 0
	system("cls"); // ����
#else
	HANDLE hConsole = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CHECK_NULLPTR(hConsole);

	// ���� �ܼ�â�� ������ �����ɴϴ�.
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	::ZeroMemory(&consoleScreenBufferInfo, sizeof(consoleScreenBufferInfo));
	if (::GetConsoleScreenBufferInfo(hConsole, &consoleScreenBufferInfo) == FALSE)
	{
		return;
	}

	// ���� X ���� = �簢�� ����
	Uint32 consoleSize = consoleScreenBufferInfo.dwSize.X * consoleScreenBufferInfo.dwSize.Y;

	// �ܼ�â�� ���۸� �������� ä��ϴ�.
	Uint32 writtenCnt = 0;
	COORD beginConsolePos = { 0, 0 };
	if (::FillConsoleOutputCharacter(hConsole, ' ', consoleSize,
		beginConsolePos, reinterpret_cast<LPDWORD>(&writtenCnt)) == FALSE)
	{
		return;
	}

	// �ܼ�â�� ���� �Ӽ��� �����մϴ�.
	if (::FillConsoleOutputAttribute(hConsole, consoleScreenBufferInfo.wAttributes,
		consoleSize, beginConsolePos, reinterpret_cast<LPDWORD>(&writtenCnt)) == FALSE)
	{
		return;
	}

	// Ŀ�� ��ġ�� ó������ �̵���ŵ�ϴ�.
	MoveConsolePos(beginConsolePos);
#endif
}

/*
ǥ�� �Է� ���۸� ���ϴ�.
*/
void CommonFunc::ClearStdInputBuffer()
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
void CommonFunc::MoveConsolePos(Int32 x, Int32 y)
{
	const COORD pos{static_cast<short>(x), static_cast<short>(y)};
	::SetConsoleCursorPosition(::GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*
COORD �����ε��Դϴ�.
*/
void CommonFunc::MoveConsolePos(const COORD& pos)
{
	::SetConsoleCursorPosition(::GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*
sizeInfo�� �̿��ؼ� �߾� �����մϴ�.
*/
void CommonFunc::AlignCenterToConsole(const SizeInfo& sizeInfo, Uint32 length)
{
	if (sizeInfo.width < length)
	{
		DEBUG_LOG("����� �۵������� ������������ ����...");
	}

	Int32 resultPosX = (sizeInfo.width / 2) - static_cast<Int32>((length / 2));
	MoveConsolePos(resultPosX, sizeInfo.height / 2);
}

/*
���� Ÿ��Ʋ�� �����մϴ�.
*/
void CommonFunc::ChangeTitle(const std::string_view& szTitle)
{
	::SetWindowText(::GetConsoleWindow(), szTitle.data());
}

/*
�α׸� ����մϴ�.
*/
void CommonFunc::ShowLog(const std::string_view& szLogCategory, const std::string_view& szLog)
{
	std::string strLog;

	if (szLogCategory.empty() == false)
	{
		strLog += "[";
		strLog += szLogCategory;
		strLog += "]: ";
	}

	strLog += szLog;
	strLog += "\n"; // �ڵ� ����!

	::OutputDebugString(strLog.c_str());
}

/*
Create�� ���� �����͸� �̿��ؼ� ó������ ���� �� ����ϰ�
Make�� ���޵� �����͵��� �����ؼ� ���� �� ����մϴ�. (��� ���� ���̴� ����...)
printf()ó�� ���� ���ڿ��� ����ϸ� std::string �ڷ������� ���ڿ��� ����ϴ�.
*/
std::string CommonFunc::MakeFormatString(const char* szFormat, ...)
{
	va_list va = nullptr;
	va_start(va, szFormat);

	// ���� ���ڿ��� ���̸� ���մϴ�.
	// �����Ҵ��� ���� ���� ���ڸ� �����ؾ� �մϴ�.
	Int32 length = _vscprintf(szFormat, va) + 1;

	// ���� ���ڷ� ���ڿ��� �����Ϸ��� �޸� ���۰� �ʿ��մϴ�.
	// std::string�� �޸� ���۰� �������̶� ����� �� �����ϴ�.
	// ����� �ܼ��ϰ� ����Ʈ ������ �����Ҵ��� ���� std::malloc()�� ����մϴ�.
	char* pMemoryBuffer = nullptr;
	pMemoryBuffer = reinterpret_cast<char*>(std::malloc(length * sizeof(char)));
	if (pMemoryBuffer == nullptr)
	{
		return std::string();
	}

	::ZeroMemory(pMemoryBuffer, (length * sizeof(char)));

	vsprintf_s(pMemoryBuffer, length, szFormat, va);
	va_end(va);

	std::string strFormat = pMemoryBuffer;
	free(pMemoryBuffer);

	return strFormat;
}

/*
���� �ܼ� ��ǥ�� �˷��ݴϴ�.
*/
COORD CommonFunc::GetCurrentConsolePos()
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
bool CommonFunc::InputNumClamp(_Out_ Int32& num, Int32 minNum, Int32 maxNum)
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
Int32 CommonFunc::Clamp(Int32 val, Int32 minVal, Int32 maxVal)
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
Clamp()�� ��������� �ּڰ����� �۾����� �ִ�����,
�ִ񰪺��� Ŀ���� �ּڰ����� ��ȯ�Ǵ� �����Դϴ�.
*/
Int32 CommonFunc::ClampCircular(Int32 val, Int32 minVal, Int32 maxVal)
{
	Int32 resultVal = val;

	if (resultVal < minVal)
	{
		resultVal = maxVal;
	}
	else if (resultVal > maxVal)
	{
		resultVal = minVal;
	}

	return resultVal;
}

/*
���� �ܼ� �ؽ�Ʈ ������ �˷��ݴϴ�.
*/
EConsoleTextColorType CommonFunc::QueryCurrentConsoleTextColor()
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
