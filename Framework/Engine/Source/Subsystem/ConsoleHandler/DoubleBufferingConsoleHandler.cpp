// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 더블 버퍼링을 이용해서 콘솔창을 다룹니다.
// =====================================================================================
#include "EnginePCH.h"
#include "DoubleBufferingConsoleHandler.h"

class DoubleBufferingConsoleHandlerInside final
{
public:
	DoubleBufferingConsoleHandlerInside() = default;
	~DoubleBufferingConsoleHandlerInside() = default;

	void SetUp();
	void CleanUp();
	void MovePosition(Int32 x, Int32 y);
	void AdjustSize(Uint32 width, Uint32 height);
	void ChangeTitle(const Char* szTitle);
	void ChangeRenderingColor(EConsoleRenderingColor renderingColor, EConsoleRenderingType renderingType);
	void ShowCursor(bool bShow);
	void RenderString(Int32 x, Int32 y, const Char* szText);
	void ClearScreen();
	void FlushInputBuffer();
	void ResetRenderingColor();
	void FlipOutputBuffer();

	COORD QueryCurrentPosition();
	Bool CheckValidCurrentOutputBuffer();

private:
	Uint32 m_defaultOutputAttr = 0; // 기본 출력 속성입니다.
	HWND m_hConsole = nullptr; // 콘솔창의 핸들입니다.
	HANDLE m_hStdInput = nullptr; // 표준 입력 버퍼의 핸들입니다.(입력 버퍼는 하나!)
	CONSOLE_SCREEN_BUFFER_INFO m_outputScreenBufferInfo; // 출력 버퍼 정보입니다.
	EnumIdx::ConsoleOutputBuffer::Data m_currentOutputBufferIdx = EnumIdx::ConsoleOutputBuffer::FRONT; // 현재 화면에 보이는 출력 버퍼입니다.
	std::array<HANDLE, EnumIdx::ConsoleOutputBuffer::COUNT> m_outputBufferHandles; // 출력 버퍼 핸들 배열입니다.
};

void DoubleBufferingConsoleHandlerInside::SetUp()
{
	ChangeTitle("Default");

	m_hConsole = ::GetConsoleWindow();
	if (m_hConsole == nullptr)
	{
		return;
	}

	m_hStdInput = ::GetStdHandle(STD_INPUT_HANDLE);
	if (m_hStdInput == nullptr)
	{
		return;
	}

	HANDLE hStdOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOutput == nullptr)
	{
		return;
	}

	::ZeroMemory(&m_outputScreenBufferInfo, sizeof(m_outputScreenBufferInfo));
	::GetConsoleScreenBufferInfo(hStdOutput, &m_outputScreenBufferInfo);
	m_defaultOutputAttr = m_outputScreenBufferInfo.wAttributes;

	for (Int32 i = 0; i < EnumIdx::ConsoleOutputBuffer::COUNT; ++i)
	{
		// 읽기와 쓰기가 가능한 콘솔창의 버퍼를 생성하는 부분이에요!
		// 더블 버퍼링에서는 콘솔창의 버퍼가 2개 필요합니다!
		HANDLE hOutputBuffer = ::CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);

		// 표준 출력 콘솔창의 정보를 복사하는 부분이에요!
		::SetConsoleScreenBufferSize(hOutputBuffer, m_outputScreenBufferInfo.dwSize);
		::SetConsoleWindowInfo(hOutputBuffer, TRUE, &m_outputScreenBufferInfo.srWindow);
		::SetConsoleTextAttribute(hOutputBuffer, m_outputScreenBufferInfo.wAttributes);

		// 정보 설정이 완료되었으니 저장할게요!
		m_outputBufferHandles[i] = hOutputBuffer;
		ShowCursor(false);
	}

	m_currentOutputBufferIdx = EnumIdx::ConsoleOutputBuffer::FRONT;

	AdjustSize(120, 30);
}

void DoubleBufferingConsoleHandlerInside::CleanUp()
{
	for (Int32 i = 0; i < EnumIdx::ConsoleOutputBuffer::COUNT; ++i)
	{
		::CloseHandle(m_outputBufferHandles[i]);
	}
}

void DoubleBufferingConsoleHandlerInside::MovePosition(Int32 x, Int32 y)
{
	COORD pos;
	pos.X = static_cast<Int16>(x);
	pos.Y = static_cast<Int16>(y);

	HANDLE hCurrentOutputBuffer = m_outputBufferHandles[m_currentOutputBufferIdx];
	if (hCurrentOutputBuffer == nullptr)
	{
		return;
	}

	::SetConsoleCursorPosition(hCurrentOutputBuffer, pos);
}

void DoubleBufferingConsoleHandlerInside::AdjustSize(Uint32 width, Uint32 height)
{
	Char buffer[DEFAULT_CHAR_BUFFER_SIZE];
	::ZeroMemory(buffer, DEFAULT_CHAR_BUFFER_SIZE);
	sprintf_s(buffer, DEFAULT_CHAR_BUFFER_SIZE, "mode con cols=%d lines=%d", width, height);
	std::system(buffer);

	m_outputScreenBufferInfo.dwSize.X = static_cast<Uint16>(width);
	m_outputScreenBufferInfo.dwSize.Y = static_cast<Uint16>(height);

	// 버퍼 사이즈와 다르게 실제 창 사이즈는 1씩 적어야 합니다.
	// 화면 좌표는 0부터 시작하므로 길이가 40이라면 0 ~ 39까지니까요.
	m_outputScreenBufferInfo.srWindow.Right = m_outputScreenBufferInfo.dwSize.X - 1;
	m_outputScreenBufferInfo.srWindow.Bottom = m_outputScreenBufferInfo.dwSize.Y - 1;
	
	for (Int32 i = 0; i < EnumIdx::ConsoleOutputBuffer::COUNT; ++i)
	{
		HANDLE hOutputBuffer = m_outputBufferHandles[i];
		if (hOutputBuffer == nullptr)
		{
			return;
		}

		::SetConsoleScreenBufferSize(hOutputBuffer, m_outputScreenBufferInfo.dwSize);
		::SetConsoleWindowInfo(hOutputBuffer, TRUE, &m_outputScreenBufferInfo.srWindow);
	}
}

void DoubleBufferingConsoleHandlerInside::ChangeTitle(const Char* szTitle)
{
	::SetWindowText(m_hConsole, szTitle);
}

void DoubleBufferingConsoleHandlerInside::ChangeRenderingColor(EConsoleRenderingColor renderingColor, EConsoleRenderingType renderingType)
{
	if ((renderingColor < EConsoleRenderingColor::BLACK) ||
		(renderingColor > EConsoleRenderingColor::BRIGHT_WHITE))
	{
		RX_ERROR(LogConsoleHandler, EErrorCode::INVALID_SCREEN_COLOR);
	}

	// CONSOLE_SCREEN_BUFFER_INFO의 wAttributes에 색상 정보가 있어요!
	// wAttributes는 2바이트로서, 하위 바이트에 색상 정보가 있습니다.
	// 거기에서도 상위 4비트는 배경색, 하위 4비트는 글자색을 의미해요.
	// 이 정보와 비트 연산을 이용하면 배경색과 글자색을 따로 알아낼 수 있습니다!	
	Uint16 attr = m_outputScreenBufferInfo.wAttributes;
	if (renderingType == EConsoleRenderingType::TEXT)
	{
		attr &= 0xFFF0; // 하위 4비트값만 가져옵니다.
		attr |= static_cast<Uint16>(renderingColor);
	}
	else if (renderingType == EConsoleRenderingType::BACKGROUND)
	{
		attr &= 0xFF0F; // 상위 4비트값만 가져옵니다.
		attr |= (static_cast<Uint16>(renderingColor) << 4); // 상위 4비트만큼 이동해야 해요!
	}
	else
	{
		RX_ERROR(LogConsoleHandler, EErrorCode::UNKNOWN);
	}

	m_outputScreenBufferInfo.wAttributes = attr;

	HANDLE hCurrentOutputBuffer = m_outputBufferHandles[m_currentOutputBufferIdx];
	if (hCurrentOutputBuffer == nullptr)
	{
		return;
	}

	if (::SetConsoleTextAttribute(hCurrentOutputBuffer, m_outputScreenBufferInfo.wAttributes) == FALSE)
	{
		RX_ERROR(LogConsoleHandler, EErrorCode::UNKNOWN);
	}
}

void DoubleBufferingConsoleHandlerInside::ShowCursor(bool bShow)
{
	HANDLE hCurrentOutputBuffer = m_outputBufferHandles[m_currentOutputBufferIdx];
	if (hCurrentOutputBuffer == nullptr)
	{
		return;
	}

	CONSOLE_CURSOR_INFO consoleCursorInfo; // 커서 정보는 CONSOLE_CURSOR_INFO에 있습니다.
	::GetConsoleCursorInfo(hCurrentOutputBuffer, &consoleCursorInfo);

	consoleCursorInfo.bVisible = bShow;
	::SetConsoleCursorInfo(hCurrentOutputBuffer, &consoleCursorInfo);
}

void DoubleBufferingConsoleHandlerInside::RenderString(Int32 x, Int32 y, const Char* szText)
{
	DWORD dwWrittenCount = 0;
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };

	HANDLE hCurrentOutputBuffer = m_outputBufferHandles[m_currentOutputBufferIdx];
	if (hCurrentOutputBuffer == nullptr)
	{
		return;
	}

	Int32 length = strlen(szText);
	::FillConsoleOutputAttribute(hCurrentOutputBuffer, m_outputScreenBufferInfo.wAttributes, length, pos, &dwWrittenCount);
	::WriteConsoleOutputCharacter(hCurrentOutputBuffer, szText, length, pos, &dwWrittenCount);
}

void DoubleBufferingConsoleHandlerInside::ClearScreen()
{
	// 가로 X 세로 = 사각형 넓이
	Uint32 size = m_outputScreenBufferInfo.dwSize.X * m_outputScreenBufferInfo.dwSize.Y;

	// 콘솔창의 버퍼를 공백으로 채웁니다.
	DWORD dwWrittenCount = 0;
	COORD beginPos = { 0, 0 };

	HANDLE hCurrentOutputBuffer = m_outputBufferHandles[m_currentOutputBufferIdx];
	if (hCurrentOutputBuffer == nullptr)
	{
		return;
	}

	if (::FillConsoleOutputCharacter(hCurrentOutputBuffer, ' ', size, beginPos, &dwWrittenCount) == FALSE)
	{
		RX_ERROR(LogConsoleHandler, EErrorCode::CLEAR_SCREEN_FAIL);
	}

	// 콘솔창 출력 버퍼 속성이 적용된 부분을 지웁니다.
	if (::FillConsoleOutputAttribute(hCurrentOutputBuffer, m_defaultOutputAttr, size, beginPos, &dwWrittenCount) == FALSE)
	{
		RX_ERROR(LogConsoleHandler, EErrorCode::CLEAR_SCREEN_FAIL);
	}

	MovePosition(beginPos.X, beginPos.Y); // 커서 위치를 처음으로 이동시킵니다.
}

void DoubleBufferingConsoleHandlerInside::FlushInputBuffer()
{
	::FlushConsoleInputBuffer(m_hStdInput);
}

void DoubleBufferingConsoleHandlerInside::ResetRenderingColor()
{
	HANDLE hCurrentOutputBuffer = m_outputBufferHandles[m_currentOutputBufferIdx];
	if (hCurrentOutputBuffer == nullptr)
	{
		return;
	}

	m_outputScreenBufferInfo.wAttributes = m_defaultOutputAttr;
	::SetConsoleTextAttribute(hCurrentOutputBuffer, m_defaultOutputAttr);
}

void DoubleBufferingConsoleHandlerInside::FlipOutputBuffer()
{
	HANDLE hCurrentOutputBuffer = m_outputBufferHandles[m_currentOutputBufferIdx];
	if (hCurrentOutputBuffer == nullptr)
	{
		return;
	}

	// 백버퍼에 렌더링한 내용을 활성화시키는 부분!
	::SetConsoleActiveScreenBuffer(hCurrentOutputBuffer);

	if (m_currentOutputBufferIdx == EnumIdx::ConsoleOutputBuffer::FRONT)
	{
		m_currentOutputBufferIdx = EnumIdx::ConsoleOutputBuffer::BACK;
	}
	else if (m_currentOutputBufferIdx == EnumIdx::ConsoleOutputBuffer::BACK)
	{
		m_currentOutputBufferIdx = EnumIdx::ConsoleOutputBuffer::FRONT;
	}
}

COORD DoubleBufferingConsoleHandlerInside::QueryCurrentPosition()
{
	HANDLE hCurrentOutputBuffer = m_outputBufferHandles[m_currentOutputBufferIdx];
	if (hCurrentOutputBuffer == nullptr)
	{
		return COORD{ 0, 0 };
	}

	::GetConsoleScreenBufferInfo(hCurrentOutputBuffer, &m_outputScreenBufferInfo);
	return m_outputScreenBufferInfo.dwCursorPosition;
}

Bool DoubleBufferingConsoleHandlerInside::CheckValidCurrentOutputBuffer()
{
	return (m_outputBufferHandles[m_currentOutputBufferIdx] != nullptr);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
DoubleBufferingConsoleHandler::DoubleBufferingConsoleHandler()
{
	m_spInside = std::make_unique<DoubleBufferingConsoleHandlerInside>();
}

/*
	콘솔창을 초기화합니다.
	콘솔창 이름과 사이즈 설정이 가능해요.
	핸들도 여기에서 저장합니다.
	더블 버퍼링을 위한 출력 버퍼를 생성하고 설정합니다.
*/
void DoubleBufferingConsoleHandler::SetUp()
{
	m_spInside->SetUp();
}

/*
	생성했던 출력 버퍼들을 정리합니다.
*/
void DoubleBufferingConsoleHandler::CleanUp()
{
	m_spInside->CleanUp();
}

/*
	현재 출력 버퍼의 출력 좌표를 옮깁니다.
*/
void DoubleBufferingConsoleHandler::MovePosition(Int32 x, Int32 y)
{
	m_spInside->MovePosition(x, y);
}

/*
	콘솔창 사이즈를 조정합니다.
*/
void DoubleBufferingConsoleHandler::AdjustSize(Uint32 width, Uint32 height)
{
	m_spInside->AdjustSize(width, height);
}

/*
	콘솔창 타이틀을 변경합니다.
*/
void DoubleBufferingConsoleHandler::ChangeTitle(const Char* szTitle)
{
	m_spInside->ChangeTitle(szTitle);
}

/*
	콘솔창 렌더링 색깔을 변경합니다.
	글자색과 배경색 중에서 선택할 수 있어요.
*/
void DoubleBufferingConsoleHandler::ChangeRenderingColor(EConsoleRenderingColor renderingColor, EConsoleRenderingType renderingType)
{
	m_spInside->ChangeRenderingColor(renderingColor, renderingType);
}

/*
	콘솔창 커서 출력 여부를 설정합니다.
	마우스 커서가 아니라 키보드 커서를 의미해요.
*/
void DoubleBufferingConsoleHandler::ShowCursor(bool bShow)
{
	m_spInside->ShowCursor(bShow);
}

/*
	현재 출력 버퍼에 글자들을 출력합니다.
	출력한 후에는 반드시 버퍼를 교체해야 합니다.
*/
void DoubleBufferingConsoleHandler::RenderString(Int32 x, Int32 y, const Char* szText)
{
	m_spInside->RenderString(x, y, szText);
}

/*
	콘솔창에 출력된 모든 것들을 지웁니다.
	출력 버퍼의 색상 정보는 그대로 유지합니다.
*/
void DoubleBufferingConsoleHandler::ClearScreen()
{
	m_spInside->ClearScreen();
}

/*
	콘솔창 입력 버퍼를 비웁니다.
	콘솔창에서는 일부 문자가 입력 버퍼에 남을 수 있으니까 주의하세요!
*/
void DoubleBufferingConsoleHandler::FlushInputBuffer()
{
	m_spInside->FlushInputBuffer();
}

/*
	콘솔창 출력 색상을 원래대로 돌립니다.
*/
void DoubleBufferingConsoleHandler::ResetRenderingColor()
{
	m_spInside->ResetRenderingColor();
}

/*
	백버퍼와 프론트버퍼를 교환합니다.
*/
void DoubleBufferingConsoleHandler::FlipOutputBuffer()
{
	m_spInside->FlipOutputBuffer();
}

void DoubleBufferingConsoleHandler::Pause() const
{
	std::system("pause");
}

/*
	정수를 입력받습니다.
*/
Int32 DoubleBufferingConsoleHandler::InputInteger()
{
	ShowCursor(true);

	Int32 value = 0;
	scanf_s("%d", &value);
	FlushInputBuffer();

	ShowCursor(false);
	return value;
}

/*
	실수를 입력받습니다.
*/
Float DoubleBufferingConsoleHandler::InputFloat()
{
	ShowCursor(true);

	Float value = 0.0f;
	scanf_s("%f", &value);
	FlushInputBuffer();

	ShowCursor(false);
	return value;
}

/*
	문자열을 입력받습니다.
*/
void DoubleBufferingConsoleHandler::InputString(OUT std::string& str)
{
	ShowCursor(true);

	Char buffer[DEFAULT_CHAR_BUFFER_SIZE];
	::ZeroMemory(buffer, DEFAULT_CHAR_BUFFER_SIZE);
	scanf_s("%[^\n]s", buffer, DEFAULT_CHAR_BUFFER_SIZE);
	FlushInputBuffer();

	ShowCursor(false);
	str.assign(buffer);
}

/*
	콘솔창 커서의 현재 좌표를 알려줍니다.
*/
COORD DoubleBufferingConsoleHandler::QueryCurrentPosition()
{
	return m_spInside->QueryCurrentPosition();
}

/*
	현재 출력 버퍼가 유효한지 확인합니다.
*/
Bool DoubleBufferingConsoleHandler::CheckValidCurrentOutputBuffer()
{
	return (m_spInside->CheckValidCurrentOutputBuffer());
}