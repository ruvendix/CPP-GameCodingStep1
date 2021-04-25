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

namespace
{
	Uint32 defaultAttr = 0;
	Char charBuffer[DEFAULT_CHAR_BUFFER_SIZE];
}

/*
	콘솔창을 초기화합니다.
	콘솔창 이름과 사이즈 설정이 가능해요.
	핸들도 여기에서 저장합니다.
	더블 버퍼링을 위한 출력 버퍼를 생성하고 설정합니다.
*/
EReturnType DoubleBufferingConsoleHandler::SetUp()
{
	ChangeTitle("Default");
	AdjustSize(60, 30);

	m_hConsole = ::GetConsoleWindow();
	RX_ASSERT(LogConsoleHandler, m_hConsole != nullptr);

	HANDLE hStdOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
	RX_ASSERT(LogConsoleHandler, hStdOutput != nullptr);

	::ZeroMemory(&m_outputScreenBufferInfo, sizeof(m_outputScreenBufferInfo));
	::GetConsoleScreenBufferInfo(hStdOutput, &m_outputScreenBufferInfo);
	defaultAttr = m_outputScreenBufferInfo.wAttributes;

	constexpr Int32 outputBufferCount = ToUnderlyingType(EConsoleOutputBufferType::COUNT);
	for (Int32 i = 0; i < outputBufferCount; ++i)
	{
		// 읽기와 쓰기가 가능한 콘솔창의 버퍼를 생성하는 부분이에요!
		// 더블 버퍼링에서는 콘솔창의 버퍼가 2개 필요합니다!
		HANDLE hOutputBuffer = ::CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
			0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);

		// 표준 출력 콘솔창의 정보를 복사하는 부분이에요!
		::SetConsoleScreenBufferSize(hOutputBuffer, m_outputScreenBufferInfo.dwSize);
		::SetConsoleWindowInfo(hOutputBuffer, TRUE, &m_outputScreenBufferInfo.srWindow);
		::SetConsoleTextAttribute(hOutputBuffer, m_outputScreenBufferInfo.wAttributes);

		// 정보 설정이 완료되었으니 저장할게요!
		m_arrOutputBuffer[i] = hOutputBuffer;
	}

	// 프론트버퍼의 키보드 커서를 가립니다.
	m_currentOutputBuffer = EConsoleOutputBufferType::FRONT;
	ShowCursor(false);

	// 백버퍼의 키보드 커서를 가립니다.
	m_currentOutputBuffer = EConsoleOutputBufferType::BACK;
	ShowCursor(false);

	return EReturnType::SUCCESS;
}

/*
	생성했던 출력 버퍼들을 정리합니다.
*/
EReturnType DoubleBufferingConsoleHandler::CleanUp()
{
	constexpr Int32 outputBufferCount = ToUnderlyingType(EConsoleOutputBufferType::COUNT);
	for (Int32 i = 0; i < outputBufferCount; ++i)
	{
		::CloseHandle(m_arrOutputBuffer[i]);
	}

	return EReturnType::SUCCESS;
}

/*
	현재 출력 버퍼의 출력 좌표를 옮깁니다.
*/
void DoubleBufferingConsoleHandler::MovePosition(Int32 x, Int32 y)
{
	COORD pos;
	pos.X = static_cast<Int16>(x);
	pos.Y = static_cast<Int16>(y);

	HANDLE hCurrentOutputBuffer = m_arrOutputBuffer[ToUnderlyingType(m_currentOutputBuffer)];
	RX_ASSERT(LogConsoleHandler, hCurrentOutputBuffer != nullptr);
	::SetConsoleCursorPosition(hCurrentOutputBuffer, pos);
}

/*
	콘솔창 사이즈를 조정합니다.
*/
void DoubleBufferingConsoleHandler::AdjustSize(Uint32 width, Uint32 height)
{
	Char buffer[DEFAULT_CHAR_BUFFER_SIZE];
	::ZeroMemory(buffer, DEFAULT_CHAR_BUFFER_SIZE);

	sprintf_s(buffer, DEFAULT_CHAR_BUFFER_SIZE, "mode con cols=%d lines=%d", width, height);
	std::system(buffer);

	m_outputScreenBufferInfo.dwSize.X = static_cast<Uint16>(width);
	m_outputScreenBufferInfo.dwSize.Y = static_cast<Uint16>(height);
}

/*
	콘솔창 타이틀을 변경합니다.
*/
void DoubleBufferingConsoleHandler::ChangeTitle(const Char* szTitle)
{
	::SetWindowText(m_hConsole, szTitle);
}

/*
	콘솔창 렌더링 색깔을 변경합니다.
	글자색과 배경색 중에서 선택할 수 있어요.
*/
EReturnType DoubleBufferingConsoleHandler::ChangeRenderingColor(EConsoleRenderingColor renderingColor, EConsoleRenderingType renderingType)
{
	if ((renderingColor < EConsoleRenderingColor::BLACK) ||
		(renderingColor > EConsoleRenderingColor::BRIGHT_WHITE))
	{
		return EReturnType::FAIL;
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
		return EReturnType::FAIL;
	}

	m_outputScreenBufferInfo.wAttributes = attr;

	HANDLE hCurrentOutputBuffer = m_arrOutputBuffer[ToUnderlyingType(m_currentOutputBuffer)];
	RX_ASSERT(LogConsoleHandler, hCurrentOutputBuffer != nullptr);

	if (::SetConsoleTextAttribute(hCurrentOutputBuffer, m_outputScreenBufferInfo.wAttributes) == FALSE)
	{
		return EReturnType::FAIL;
	}

	return EReturnType::SUCCESS;
}

/*
	콘솔창 커서 출력 여부를 설정합니다.
	마우스 커서가 아니라 키보드 커서를 의미해요.
*/
void DoubleBufferingConsoleHandler::ShowCursor(bool bShow)
{
	HANDLE hCurrentOutputBuffer = m_arrOutputBuffer[ToUnderlyingType(m_currentOutputBuffer)];
	RX_ASSERT(LogConsoleHandler, hCurrentOutputBuffer != nullptr);

	CONSOLE_CURSOR_INFO consoleCursorInfo; // 커서 정보는 CONSOLE_CURSOR_INFO에 있습니다.
	::GetConsoleCursorInfo(hCurrentOutputBuffer, &consoleCursorInfo);

	consoleCursorInfo.bVisible = bShow;
	::SetConsoleCursorInfo(hCurrentOutputBuffer, &consoleCursorInfo);
}

/*
	현재 출력 버퍼에 글자들을 출력합니다.
	출력한 후에는 반드시 버퍼를 교체해야 합니다.
*/
void DoubleBufferingConsoleHandler::RenderString(Int32 x, Int32 y, const Char* szText)
{
	DWORD dwWrittenCount = 0;
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };

	HANDLE hCurrentOutputBuffer = m_arrOutputBuffer[ToUnderlyingType(m_currentOutputBuffer)];
	RX_ASSERT(LogConsoleHandler, hCurrentOutputBuffer != nullptr);

	Int32 length = strlen(szText);
	::FillConsoleOutputAttribute(hCurrentOutputBuffer, m_outputScreenBufferInfo.wAttributes, length, pos, &dwWrittenCount);
	::WriteConsoleOutputCharacter(hCurrentOutputBuffer, szText, length, pos, &dwWrittenCount);
}

/*
	콘솔창에 출력된 모든 것들을 지웁니다.
	출력 버퍼의 색상 정보는 그대로 유지합니다.
*/
EReturnType DoubleBufferingConsoleHandler::ClearScreen()
{
	// 가로 X 세로 = 사각형 넓이
	Uint32 size = m_outputScreenBufferInfo.dwSize.X * m_outputScreenBufferInfo.dwSize.Y;

	// 콘솔창의 버퍼를 공백으로 채웁니다.
	DWORD dwWrittenCount = 0;
	COORD beginPos = { 0, 0 };

	HANDLE hCurrentOutputBuffer = m_arrOutputBuffer[ToUnderlyingType(m_currentOutputBuffer)];
	RX_ASSERT(LogConsoleHandler, hCurrentOutputBuffer != nullptr);

	if (::FillConsoleOutputCharacter(hCurrentOutputBuffer, ' ', size, beginPos, &dwWrittenCount) == FALSE)
	{
		return EReturnType::FAIL;
	}

	// 콘솔창 출력 버퍼 속성이 적용된 부분을 지웁니다.
	if (::FillConsoleOutputAttribute(hCurrentOutputBuffer, defaultAttr, size, beginPos, &dwWrittenCount) == FALSE)
	{
		return EReturnType::FAIL;
	}

	MovePosition(beginPos.X, beginPos.Y); // 커서 위치를 처음으로 이동시킵니다.
	return EReturnType::SUCCESS;
}

/*
	콘솔창 입력 버퍼를 비웁니다.
	콘솔창에서는 일부 문자가 입력 버퍼에 남을 수 있으니까 주의하세요!
*/
void DoubleBufferingConsoleHandler::FlushInputBuffer()
{
	HANDLE hCurrentOutputBuffer = m_arrOutputBuffer[ToUnderlyingType(m_currentOutputBuffer)];
	RX_ASSERT(LogConsoleHandler, hCurrentOutputBuffer != nullptr);
	::FlushConsoleInputBuffer(hCurrentOutputBuffer);
}

/*
	콘솔창 출력 색상을 원래대로 돌립니다.
*/
void DoubleBufferingConsoleHandler::ResetRenderingColor()
{
	HANDLE hCurrentOutputBuffer = m_arrOutputBuffer[ToUnderlyingType(m_currentOutputBuffer)];
	RX_ASSERT(LogConsoleHandler, hCurrentOutputBuffer != nullptr);

	m_outputScreenBufferInfo.wAttributes = defaultAttr;
	::SetConsoleTextAttribute(hCurrentOutputBuffer, defaultAttr);
}

/*
	백버퍼와 프론트버퍼를 교환합니다.
*/
void DoubleBufferingConsoleHandler::FlipOutputBuffer()
{
	HANDLE hCurrentOutputBuffer = m_arrOutputBuffer[ToUnderlyingType(m_currentOutputBuffer)];
	RX_ASSERT(LogConsoleHandler, hCurrentOutputBuffer != nullptr);

	// 백버퍼에 렌더링한 내용을 활성화시키는 부분!
	::SetConsoleActiveScreenBuffer(hCurrentOutputBuffer);

	if (m_currentOutputBuffer == EConsoleOutputBufferType::FRONT)
	{
		m_currentOutputBuffer = EConsoleOutputBufferType::BACK;
	}
	else if (m_currentOutputBuffer == EConsoleOutputBufferType::BACK)
	{
		m_currentOutputBuffer = EConsoleOutputBufferType::FRONT;
	}
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
const Char* DoubleBufferingConsoleHandler::InputString()
{
	ShowCursor(true);

	::ZeroMemory(charBuffer, DEFAULT_CHAR_BUFFER_SIZE);
	scanf_s("%[^\n]s", charBuffer, DEFAULT_CHAR_BUFFER_SIZE);
	FlushInputBuffer();

	ShowCursor(false);
	return charBuffer;
}

/*
	콘솔창 커서의 현재 좌표를 알려줍니다.
*/
COORD DoubleBufferingConsoleHandler::QueryCurrentPosition()
{
	HANDLE hCurrentOutputBuffer = m_arrOutputBuffer[ToUnderlyingType(m_currentOutputBuffer)];
	RX_ASSERT(LogConsoleHandler, hCurrentOutputBuffer != nullptr);

	::GetConsoleScreenBufferInfo(hCurrentOutputBuffer, &m_outputScreenBufferInfo);
	return m_outputScreenBufferInfo.dwCursorPosition;
}