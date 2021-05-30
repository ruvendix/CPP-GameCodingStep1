// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ܼ�â�� �ٷ� �� ���˴ϴ�.
// =====================================================================================
#include "EnginePCH.h"
#include "ConsoleHandler.h"

namespace
{
	Uint32 defaultAttr = 0;
	Char charBuffer[DEFAULT_CHAR_BUFFER_SIZE];
}

/*
	�ܼ�â�� �ʱ�ȭ�մϴ�.
	�ܼ�â �̸��� ������ ������ �����ؿ�.
	�ڵ鵵 ���⿡�� �����մϴ�.
*/
void ConsoleHandler::SetUp()
{
	m_hConsole = ::GetConsoleWindow();
	RX_ASSERT(LogConsoleHandler, m_hConsole != nullptr);

	m_hStdInput = ::GetStdHandle(STD_INPUT_HANDLE);
	RX_ASSERT(LogConsoleHandler, m_hStdInput != nullptr);

	m_hStdOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
	RX_ASSERT(LogConsoleHandler, m_hStdOutput != nullptr);

	::GetConsoleScreenBufferInfo(m_hStdOutput, &m_outputScreenBufferInfo);
	defaultAttr = m_outputScreenBufferInfo.wAttributes;

	ChangeTitle("Default");
	AdjustSize(60, 30);
}

/*
	�ܼ�â�� �����մϴ�.
	������ �߰��� ������ �����.
*/
void ConsoleHandler::CleanUp()
{
	
}

/*
	�ܼ�â Ŀ���� ��ǥ�� �ű�ϴ�.
*/
void ConsoleHandler::MovePosition(Int32 x, Int32 y)
{
	COORD pos;
	pos.X = static_cast<Int16>(x);
	pos.Y = static_cast<Int16>(y);

	::SetConsoleCursorPosition(m_hStdOutput, pos);
}

/*
	�ܼ�â ����� �����մϴ�.
*/
void ConsoleHandler::AdjustSize(Uint32 width, Uint32 height)
{
	Char buffer[DEFAULT_CHAR_BUFFER_SIZE];
	::ZeroMemory(buffer, DEFAULT_CHAR_BUFFER_SIZE);

	sprintf_s(buffer, DEFAULT_CHAR_BUFFER_SIZE, "mode con cols=%d lines=%d", width, height);
	std::system(buffer);

	m_outputScreenBufferInfo.dwSize.X = static_cast<Uint16>(width);
	m_outputScreenBufferInfo.dwSize.Y = static_cast<Uint16>(height);
}

/*
	�ܼ�â Ÿ��Ʋ�� �����մϴ�.
*/
void ConsoleHandler::ChangeTitle(const Char* szTitle)
{
	::SetWindowText(m_hConsole, szTitle);
}

/*
	�ܼ�â ������ ������ �����մϴ�.
	���ڻ��� ���� �߿��� ������ �� �־��.
*/
void ConsoleHandler::ChangeRenderingColor(EConsoleRenderingColor renderingColor, EConsoleRenderingType renderingType)
{
	if ((renderingColor < EConsoleRenderingColor::BLACK) ||
		(renderingColor > EConsoleRenderingColor::BRIGHT_WHITE))
	{
		RX_ERROR(LogConsoleHandler, EErrorCode::INVALID_SCREEN_COLOR);
	}

	// CONSOLE_SCREEN_BUFFER_INFO�� wAttributes�� ���� ������ �־��!
	// wAttributes�� 2����Ʈ�μ�, ���� ����Ʈ�� ���� ������ �ֽ��ϴ�.
	// �ű⿡���� ���� 4��Ʈ�� ����, ���� 4��Ʈ�� ���ڻ��� �ǹ��ؿ�.
	// �� ������ ��Ʈ ������ �̿��ϸ� ������ ���ڻ��� ���� �˾Ƴ� �� �ֽ��ϴ�!	
	Uint16 attr = m_outputScreenBufferInfo.wAttributes;
	if (renderingType == EConsoleRenderingType::TEXT)
	{
		attr &= 0xFFF0; // ���� 4��Ʈ���� �����ɴϴ�.
		attr |= static_cast<Uint16>(renderingColor);
	}
	else if (renderingType == EConsoleRenderingType::BACKGROUND)
	{
		attr &= 0xFF0F; // ���� 4��Ʈ���� �����ɴϴ�.
		attr |= (static_cast<Uint16>(renderingColor) << 4); // ���� 4��Ʈ��ŭ �̵��ؾ� �ؿ�!
	}
	else
	{
		RX_ERROR(LogConsoleHandler, EErrorCode::UNKNOWN);
	}

	m_outputScreenBufferInfo.wAttributes = attr;
	if (::SetConsoleTextAttribute(m_hStdOutput, m_outputScreenBufferInfo.wAttributes) == FALSE)
	{
		RX_ERROR(LogConsoleHandler, EErrorCode::UNKNOWN);
	}
}

/*
	�ܼ�â Ŀ�� ��� ���θ� �����մϴ�.
	���콺 Ŀ���� �ƴ϶� Ű���� Ŀ���� �ǹ��ؿ�.
*/
void ConsoleHandler::ShowCursor(bool bShow)
{
	CONSOLE_CURSOR_INFO consoleCursorInfo; // Ŀ�� ������ CONSOLE_CURSOR_INFO�� �ֽ��ϴ�.
	::GetConsoleCursorInfo(m_hStdOutput, &consoleCursorInfo);

	consoleCursorInfo.bVisible = bShow;
	::SetConsoleCursorInfo(m_hStdOutput, &consoleCursorInfo);
}

/*
	�ܼ�â�� ���ڵ��� ����մϴ�.
*/
void ConsoleHandler::RenderString(Int32 x, Int32 y, const Char* szText)
{
	MovePosition(x, y);
	printf("%s\n", szText);
}

/*
	�ܼ�â�� ��µ� ��� �͵��� ����ϴ�.
	��� ������ ���� ������ �״�� �����մϴ�.
*/
void ConsoleHandler::ClearScreen()
{
	// ���� X ���� = �簢�� ����
	Uint32 size = m_outputScreenBufferInfo.dwSize.X * m_outputScreenBufferInfo.dwSize.Y;

	// �ܼ�â�� ���۸� �������� ä��ϴ�.
	DWORD dwWrittenCnt = 0;
	COORD beginPos = { 0, 0 };
	if (::FillConsoleOutputCharacter(m_hStdOutput, ' ', size, beginPos, &dwWrittenCnt) == FALSE)
	{
		RX_ERROR(LogConsoleHandler, EErrorCode::FAILED_CLEAR_SCREEN);
	}

	// �ܼ�â ��� ���� �Ӽ��� ����� �κ��� ����ϴ�.
	if (::FillConsoleOutputAttribute(m_hStdOutput, defaultAttr, size, beginPos, &dwWrittenCnt) == FALSE)
	{
		RX_ERROR(LogConsoleHandler, EErrorCode::FAILED_CLEAR_SCREEN);
	}

	MovePosition(beginPos.X, beginPos.Y); // Ŀ�� ��ġ�� ó������ �̵���ŵ�ϴ�.	
}

/*
	�ܼ�â �Է� ���۸� ���ϴ�.
	�ܼ�â������ �Ϻ� ���ڰ� �Է� ���ۿ� ���� �� �����ϱ� �����ϼ���!
*/
void ConsoleHandler::FlushInputBuffer()
{
	::FlushConsoleInputBuffer(m_hStdInput);
}

/*
	�ܼ�â ��� ������ ������� �����ϴ�.
*/
void ConsoleHandler::ResetRenderingColor()
{
	m_outputScreenBufferInfo.wAttributes = defaultAttr;
	::SetConsoleTextAttribute(m_hStdOutput, defaultAttr);
}

void ConsoleHandler::Pause() const
{
	std::system("pause");
}

/*
	������ �Է¹޽��ϴ�.
*/
Int32 ConsoleHandler::InputInteger()
{
	Int32 value = 0;
	scanf_s("%d", &value);
	FlushInputBuffer();
	return value;
}

/*
	�Ǽ��� �Է¹޽��ϴ�.
*/
Float ConsoleHandler::InputFloat()
{
	Float value = 0.0f;
	scanf_s("%f", &value);
	FlushInputBuffer();
	return value;
}

/*
	���ڿ��� �Է¹޽��ϴ�.
*/
const Char* ConsoleHandler::InputString()
{
	::ZeroMemory(charBuffer, DEFAULT_CHAR_BUFFER_SIZE);
	scanf_s("%[^\n]s", charBuffer, DEFAULT_CHAR_BUFFER_SIZE);
	FlushInputBuffer();
	return charBuffer;
}

/*
	�ܼ�â Ŀ���� ���� ��ǥ�� �˷��ݴϴ�.
*/
COORD ConsoleHandler::QueryCurrentPosition()
{
	::GetConsoleScreenBufferInfo(m_hStdOutput, &m_outputScreenBufferInfo);
	return m_outputScreenBufferInfo.dwCursorPosition;
}