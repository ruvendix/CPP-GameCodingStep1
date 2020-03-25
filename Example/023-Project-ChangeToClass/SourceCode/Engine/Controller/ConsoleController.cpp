// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 콘솔창의 여러 속성을 제어하는 컨트롤러입니다.
// 더블 버퍼링은 ACTIVATION_CONSOLE_DBL_BUFFERING을 전처리기에 추가해야 작동됩니다.
// =====================================================================================

#include "PCH.h"
#include "ConsoleController.h"

#include "Context\ConfigContext.h"

DEFINE_LOG_CATEGORY(ConsoleController);
DEFINE_PHOENIX_SINGLETON(ConsoleController);

/*
콘솔창을 초기화합니다.
ACTIVATION_CONSOLE_DBL_BUFFERING이 활성화된 상태라면 더블 버퍼링 관련 작업을 처리합니다.
*/
void ConsoleController::Initialize(const std::string_view& szTitle, const SizeInfo& sizeInfo)
{
	ConsoleController::I()->ChangeTitle(szTitle);
	ConsoleController::I()->AdjustConsoleArea(sizeInfo);
	ConsoleController::I()->DefaultConsoleGameStyle();

#ifdef ACTIVATION_CONSOLE_DBL_BUFFERING
	// 표준 출력 콘솔창의 버퍼 정보를 가져오는 부분이에요!
	::ZeroMemory(&m_consoleScreenBufferInfo, sizeof(m_consoleScreenBufferInfo));
	::GetConsoleScreenBufferInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &m_consoleScreenBufferInfo);

	// 표준 출력 콘솔창의 커서 정보를 가져오는 부분이에요!
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	::ZeroMemory(&consoleCursorInfo, sizeof(consoleCursorInfo));
	::GetConsoleCursorInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);

	for (Int32 i = 0; i < CommonFunc::ToUnderlyingType(EConsoleScreenBufferTypeIdx::MAX); ++i)
	{
		// 읽기와 쓰기가 가능한 콘솔창의 버퍼를 생성하는 부분이에요!
		// 더블 버퍼링에서는 콘솔창의 버퍼가 2개 필요합니다!
		HANDLE hConsoleScreenBuffer =
			::CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);

		// 표준 출력 콘솔창의 정보로 복사하는 부분이에요!
		::SetConsoleScreenBufferSize(hConsoleScreenBuffer, m_consoleScreenBufferInfo.dwSize);
		::SetConsoleWindowInfo(hConsoleScreenBuffer, TRUE, &m_consoleScreenBufferInfo.srWindow);
		::SetConsoleTextAttribute(hConsoleScreenBuffer, m_consoleScreenBufferInfo.wAttributes);
		::SetConsoleCursorInfo(hConsoleScreenBuffer, &consoleCursorInfo);

		// 정보 설정이 완료되었으니 저장할게요!
		m_hConsoleScreenBuffers[i] = hConsoleScreenBuffer;
	}

	m_currentConsoleScreenBufferType = EConsoleScreenBufferTypeIdx::BACK;
#else
	m_hConsoleScreenBuffers[CommonFunc::ToUnderlyingType(EConsoleScreenBufferType::FRONT)] = ::GetStdHandle(STD_OUTPUT_HANDLE);
#endif

	// 표준 입력 콘솔창에 "Ctrl + C" 무효와 "마우스 입력 가능"을 추가할게요!
	DWORD dwMode = 0;
	::GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &dwMode);
	::SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), dwMode | ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	// 커서는 표시하지 않을게요!
	ShowConsoleCursor(false);

	m_pCurrentConsoleSelector = trace_new ConsoleSelector;
}

/*
프론트버퍼가 활성화되어있으면 백버퍼로,
백버퍼가 활성화되어있으면 프론트버퍼로 변경합니다.
*/
void ConsoleController::Flipping()
{
	// 버퍼에 렌더링한 내용을 활성화시키는 부분!
	::SetConsoleActiveScreenBuffer(getCurrentConsoleScreenBufferHandle());

	if (m_currentConsoleScreenBufferType == EConsoleScreenBufferTypeIdx::FRONT)
	{
		m_currentConsoleScreenBufferType = EConsoleScreenBufferTypeIdx::BACK;
	}
	else if (m_currentConsoleScreenBufferType == EConsoleScreenBufferTypeIdx::BACK)
	{
		m_currentConsoleScreenBufferType = EConsoleScreenBufferTypeIdx::FRONT;
	}
	else
	{
		DEFAULT_ERROR_HANDLER(EErrorType::UNKNOWN_CONSOLE_SCREEN_BUFFER_TYPE);
		return;
	}
}

/*
콘솔창의 핸들을 닫습니다.
*/
void ConsoleController::Finalize()
{
#ifdef ACTIVATION_CONSOLE_DBL_BUFFERING
	for (Int32 i = 0; i < CommonFunc::ToUnderlyingType(EConsoleScreenBufferTypeIdx::MAX); ++i)
	{
		::CloseHandle(m_hConsoleScreenBuffers[i]);
	}
#else
	::CloseHandle(m_hConsoleScreenBuffers[CommonFunc::ToUnderlyingType(EConsoleScreenBufferType::FRONT)]);
#endif

	SAFE_DELETE(m_pCurrentConsoleSelector);
}

/*
콘솔창에 문자열을 출력합니다.
더블 버퍼링인 경우, 활성화되지 않은 버퍼에 문자열을 출력합니다.
*/
void ConsoleController::PrintString(Int32 x, Int32 y, const std::string_view& szOutput)
{
	DWORD dwWrittenCnt = 0;
	COORD printPos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	HANDLE hConsoleScreenBuffer = getCurrentConsoleScreenBufferHandle();

	::FillConsoleOutputAttribute(hConsoleScreenBuffer, m_consoleScreenBufferInfo.wAttributes, szOutput.size(), printPos, &dwWrittenCnt);
	::WriteConsoleOutputCharacter(hConsoleScreenBuffer, szOutput.data(), szOutput.size(), printPos, &dwWrittenCnt);
}

/*
콘솔창의 영역을 조정합니다.
*/
void ConsoleController::AdjustConsoleArea(Uint32 width, Uint32 height)
{
	std::string strConsoleProperty = CommonFunc::MakeFormatString("mode con cols=%d lines=%d", width, height);
	system(strConsoleProperty.c_str());

	ConfigCtx::I()->setResoultion(SizeInfo{ width, height });
}

/*
AdjustConsoleArea()의 SizeInfo 오버로딩입니다.
*/
void ConsoleController::AdjustConsoleArea(const SizeInfo& sizeInfo)
{
	AdjustConsoleArea(sizeInfo.width, sizeInfo.height);
}

/*
콘솔창의 스타일을 게임용으로 설정합니다.
최대화, 최소화, 닫기 버튼이 없고 영역이 고정됩니다.
*/
void ConsoleController::DefaultConsoleGameStyle()
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
void ConsoleController::PauseGame()
{
	system("pause");
}

/*
콘솔창의 전체 영역을 깨끗하게 지웁니다.
참고 : https://docs.microsoft.com/en-us/windows/console/clearing-the-screen
*/
void ConsoleController::ClearConsoleScreen()
{
#if 0
	system("cls"); // 느려
#else
	HANDLE hConsoleScreenBuffer = getCurrentConsoleScreenBufferHandle();

	// 가로 X 세로 = 사각형 넓이
	Uint32 consoleSize = m_consoleScreenBufferInfo.dwSize.X * m_consoleScreenBufferInfo.dwSize.Y;

	// 콘솔창의 버퍼를 공백으로 채웁니다.
	DWORD dwWrittenCnt = 0;
	COORD beginConsolePos = { 0, 0 };
	if (::FillConsoleOutputCharacter(hConsoleScreenBuffer, ' ', consoleSize, beginConsolePos, &dwWrittenCnt) == FALSE)
	{
		return;
	}

	// 콘솔창의 버퍼 속성을 설정합니다.
	if (::FillConsoleOutputAttribute(hConsoleScreenBuffer, m_consoleScreenBufferInfo.wAttributes, consoleSize, beginConsolePos, &dwWrittenCnt) == FALSE)
	{
		return;
	}

	// 커서 위치를 처음으로 이동시킵니다.
	MoveConsolePos(beginConsolePos);
#endif
}

/*
표준 입력 버퍼를 비웁니다.
*/
void ConsoleController::ClearStdInputBuffer()
{
	char value = '0'; // EOF나 '\n'만 아니면 괜찮아요.

	// 표준 입력 버퍼를 비우는 방법이에요.
	// std::fflush(stdin)도 있지만, 표준에는 적합하지 않아서 생략할게요.
	while ( (value != EOF) &&
		    (value != '\n') )
	{
		value = static_cast<char>(getchar());
	}
}

/*
콘솔창의 좌표를 이동시킵니다.
*/
void ConsoleController::MoveConsolePos(Int32 x, Int32 y)
{
	COORD pos{ static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(getCurrentConsoleScreenBufferHandle(), pos);
}

/*
MoveConsolePos()의 COORD 오버로딩입니다.
*/
void ConsoleController::MoveConsolePos(const COORD& pos)
{
	MoveConsolePos(pos.X, pos.Y);
}

/*
sizeInfo를 이용해서 중앙 정렬합니다.
*/
void ConsoleController::AlignCenter(const SizeInfo& sizeInfo, Uint32 length)
{
	if (sizeInfo.width < length)
	{
		DEBUG_LOG("기능은 작동하지만 정상적이지는 않음...");
	}

	Int32 resultPosX = (sizeInfo.width / 2) - static_cast<Int32>((length / 2));
	MoveConsolePos(resultPosX, sizeInfo.height / 2);
}

/*
콘솔창의 타이틀을 변경합니다.
*/
void ConsoleController::ChangeTitle(const std::string_view& szTitle)
{
	::SetWindowText(::GetConsoleWindow(), szTitle.data());
}

/*
콘솔창의 출력 색상을 변경합니다.
글자 색상과 배경 색상 둘 다 변경 가능합니다.
*/
void ConsoleController::ChangeConsoleOutputColor(EConsoleOutputType consoleOutputType, EConsoleOutputColorType consoleOutputColorType)
{
	if ( (consoleOutputColorType < EConsoleOutputColorType::BLACK) ||
		 (consoleOutputColorType > EConsoleOutputColorType::BRIGHT_WHITE) )
	{
		DEFAULT_ERROR_HANDLER(EErrorType::UNKNOWN_CONSOLE_COLOR);
		return;
	}

	// CONSOLE_SCREEN_BUFFER_INFO의 wAttributes에 색상 정보가 있어요!
	// 하위 1바이트에서 상위 4비트는 배경 색상, 하위 4비트는 글자 색상을 의미하죠.
	// 이 정보와 비트 연산을 이용하면 배경 색상과 글자 색상을 따로 알아낼 수 있습니다!
	WORD consoleScreenBufferAttr = m_consoleScreenBufferInfo.wAttributes;
	if (consoleOutputType == EConsoleOutputType::TEXT)
	{
		consoleScreenBufferAttr &= 0xFFF0;
		consoleScreenBufferAttr |= static_cast<BYTE>(consoleOutputColorType);
	}
	else if (consoleOutputType == EConsoleOutputType::BACKGROUND)
	{
		consoleScreenBufferAttr = m_consoleScreenBufferInfo.wAttributes & 0xFF0F;
		consoleScreenBufferAttr |= (static_cast<BYTE>(consoleOutputColorType) << 4);
	}
	else
	{
		DEFAULT_ERROR_HANDLER(EErrorType::UNKNOWN_CONSOLE_OUTPUT_TYPE);
	}

	m_consoleScreenBufferInfo.wAttributes = consoleScreenBufferAttr;
	::SetConsoleTextAttribute(getCurrentConsoleScreenBufferHandle(), m_consoleScreenBufferInfo.wAttributes);

	return;
}

/*
콘솔창의 커서 출력 여부를 설정합니다.
마우스 커서가 아니라 키보드 커서를 의미합니다.
*/
void ConsoleController::ShowConsoleCursor(bool bShow)
{
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	::ZeroMemory(&consoleCursorInfo, sizeof(consoleCursorInfo));

	for (Uint32 i = 0; i < static_cast<Uint32>(EConsoleScreenBufferTypeIdx::MAX); ++i)
	{
		HANDLE hConsoleScreenBuffer = m_hConsoleScreenBuffers[i];
		::GetConsoleCursorInfo(hConsoleScreenBuffer, &consoleCursorInfo);

		consoleCursorInfo.bVisible = bShow;
		::SetConsoleCursorInfo(hConsoleScreenBuffer, &consoleCursorInfo);
	}
}

void ConsoleController::RestoreConsoleSelector()
{
	*m_pCurrentConsoleSelector = *(m_stackConsoleSelector.top());
	m_stackConsoleSelector.pop();
}

void ConsoleController::PushBackupConsoleSelector()
{
	m_stackConsoleSelector.push(std::make_unique<ConsoleSelector>(*m_pCurrentConsoleSelector));
}

void ConsoleController::AddSelectorPosX(Int32 x)
{
	m_pCurrentConsoleSelector->AddSelectorPosX(x);
}

void ConsoleController::AddSelectorPosY(Int32 y)
{
	m_pCurrentConsoleSelector->AddSelectorPosY(y);
}

void ConsoleController::DrawSelector() const
{
	m_pCurrentConsoleSelector->OnDrawSelector();
}

const COORD& ConsoleController::GetCurrentConsoleSelectorPos() const
{
	return m_pCurrentConsoleSelector->getSelectorPos();
}

void ConsoleController::SetCurrentConsoleSelectorPos(const COORD& pos)
{
	m_pCurrentConsoleSelector->setSelectorPos(pos);
}

/*
콘솔창의 좌표를 알려줍니다.
*/
COORD ConsoleController::QueryCurrentConsolePos()
{
	COORD pos = { 0, 0 };

	::GetConsoleScreenBufferInfo(getCurrentConsoleScreenBufferHandle(), &m_consoleScreenBufferInfo);
	pos.X = m_consoleScreenBufferInfo.dwCursorPosition.X;
	pos.Y = m_consoleScreenBufferInfo.dwCursorPosition.Y;

	return pos;
}

/*
현재 콘솔 텍스트 색상을 알려줍니다.
*/
EConsoleOutputColorType ConsoleController::QueryCurrentConsoleOutputColor(EConsoleOutputType consoleOutputType) const
{
	// CONSOLE_SCREEN_BUFFER_INFO의 wAttributes에 색상 정보가 있어요!
	// 하위 1바이트에서 상위 4비트는 배경 색상, 하위 4비트는 글자 색상을 의미하죠.
	// 이 정보와 비트 연산을 이용하면 배경 색상과 글자 색상을 따로 알아낼 수 있습니다!
	BYTE consoleColor = 0;
	if (consoleOutputType == EConsoleOutputType::TEXT)
	{
		consoleColor = static_cast<BYTE>(m_consoleScreenBufferInfo.wAttributes & 0x000F);
	}
	else if (consoleOutputType == EConsoleOutputType::BACKGROUND)
	{
		consoleColor = static_cast<BYTE>((m_consoleScreenBufferInfo.wAttributes & 0x00F0) >> 4);
	}
	else
	{
		DEFAULT_ERROR_HANDLER(EErrorType::UNKNOWN_CONSOLE_OUTPUT_TYPE);
	}

	if ( (consoleColor < static_cast<INT32>(EConsoleOutputColorType::BLACK)) ||
		 (consoleColor > static_cast<INT32>(EConsoleOutputColorType::BRIGHT_WHITE)) )
	{
		DEFAULT_ERROR_HANDLER(EErrorType::UNKNOWN_CONSOLE_COLOR);
		return EConsoleOutputColorType::UNKNOWN;
	}

	return static_cast<EConsoleOutputColorType>(consoleColor);
}
