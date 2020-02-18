// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 공용으로 사용되는 함수 정의 모음입니다.
// =====================================================================================

#include "PCH.h"
#include "CommonFunc.h"

/*
	콘솔 영역을 조정합니다.
*/
void CommonFunc::AdjustConsoleArea(Int32 width, Int32 height)
{
	std::string strConsoleProperty = MakeFormatString("mode con cols=%d lines=%d", width, height);
	system(strConsoleProperty.c_str());
}

/*
	SizeInfo 오버로딩입니다.
*/
void CommonFunc::AdjustConsoleArea(const SizeInfo& sizeInfo)
{
	AdjustConsoleArea(sizeInfo.width, sizeInfo.height);
}

/*
	게임용 콘솔 스타일로 설정합니다.
	최대화, 최소화, 닫기 버튼이 없고 영역이 고정됩니다.
*/
void CommonFunc::GameConsoleStyle()
{
	HWND hConsoleWnd = ::GetConsoleWindow();
	DWORD style = ::GetWindowLong(hConsoleWnd, GWL_STYLE);
	style &= ~(WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME); // WS_MAXIMIZEBOX와 WS_THICKFRAME 제외시키기
	::SetWindowLong(hConsoleWnd, GWL_STYLE, style);

	// 닫기 버튼을 비활성하는 방법
	HMENU hSysMenu = ::GetSystemMenu(hConsoleWnd, FALSE);
	::DeleteMenu(hSysMenu, SC_CLOSE, MF_BYCOMMAND);
}

/*
    응용 프로그램을 잠시 멈춥니다.
*/
void CommonFunc::PauseGameApp()
{
	system("pause");
}

/*
    콘솔창을 깨끗하게 지웁니다.
*/
void CommonFunc::ClearConsoleScreen()
{
	system("cls");
}

/*
	표준 입력 버퍼를 비웁니다.
*/
void CommonFunc::ClearStdInputBuffer()
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
void CommonFunc::MoveConsolePos(Int32 x, Int32 y)
{
	const COORD pos{static_cast<short>(x), static_cast<short>(y)};
	::SetConsoleCursorPosition(::GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*
	COORD 오버로딩입니다.
*/
void CommonFunc::MoveConsolePos(const COORD& pos)
{
	::SetConsoleCursorPosition(::GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*
	sizeInfo를 이용해서 중앙 정렬합니다.
*/
void CommonFunc::AlignCenterToConsole(const SizeInfo& sizeInfo, Uint32 length)
{
	if (sizeInfo.width < length)
	{
		DEBUG_LOG("기능은 작동하지만 정상적이지는 않음...");
	}

	Int32 resultPosX = (sizeInfo.width / 2) - static_cast<Int32>((length / 2));
	MoveConsolePos(resultPosX, sizeInfo.height / 2);
}

void CommonFunc::ChangeTitle(const std::string_view& szTitle)
{
	::SetWindowText(::GetConsoleWindow(), szTitle.data());
}

/*
	로그를 출력합니다.
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
	strLog += "\n"; // 자동 개행!

	::OutputDebugString(strLog.c_str());
}

/*
    Create은 생성 데이터를 이용해서 처음부터 만들 때 사용하고
    Make는 전달된 데이터들을 조합해서 만들 때 사용합니다. (사실 별로 차이는 없음...)
    printf()처럼 서식 문자열을 사용하면 std::string 자료형으로 문자열을 만듭니다.
*/
std::string CommonFunc::MakeFormatString(const char* szFormat, ...)
{
	va_list va = nullptr;
	va_start(va, szFormat);

	// 서식 문자열의 길이를 구합니다.
	// 동적할당을 위해 종료 문자를 포함해야 합니다.
	Int32 length = _vscprintf(szFormat, va) + 1;

	// 가변 인자로 문자열을 조합하려면 메모리 버퍼가 필요합니다.
	// std::string은 메모리 버퍼가 가변적이라 사용할 수 없습니다.
	// 참고로 단순하게 바이트 단위로 동적할당할 때는 std::malloc()을 사용합니다.
	char* pMemBuffer = nullptr;
	pMemBuffer = reinterpret_cast<char*>(std::malloc(length * sizeof(char)));
	if (pMemBuffer == nullptr)
	{
		return std::string();
	}

	::ZeroMemory(pMemBuffer, (length * sizeof(char)));

	vsprintf_s(pMemBuffer, length, szFormat, va);
	va_end(va);

	std::string strFormat = pMemBuffer;
	free(pMemBuffer);

	return strFormat;
}

/*
    현재 콘솔 좌표를 알려줍니다.
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
    숫자를 입력 받음과 동시에 입력 범위를 벗어나면 범위 안으로 자동 조절합니다.
*/
bool CommonFunc::InputNumClamp(_Out_ Int32& num, Int32 minNum, Int32 maxNum)
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
    현재 콘솔 텍스트 색상을 알려줍니다.
*/
EConsoleTextColorType CommonFunc::QueryCurrentConsoleTextColor()
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
