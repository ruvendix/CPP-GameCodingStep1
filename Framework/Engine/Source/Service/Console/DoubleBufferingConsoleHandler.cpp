// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ���۸��� �̿��ؼ� �ܼ�â�� �ٷ�ϴ�.
// =====================================================================================
#include "EnginePCH.h"
#include "DoubleBufferingConsoleHandler.h"

namespace
{
	Uint32 defaultAttr = 0;
	Char charBuffer[DEFAULT_CHAR_BUFFER_SIZE];
}

/*
	�ܼ�â�� �ʱ�ȭ�մϴ�.
	�ܼ�â �̸��� ������ ������ �����ؿ�.
	�ڵ鵵 ���⿡�� �����մϴ�.
	���� ���۸��� ���� ��� ���۸� �����ϰ� �����մϴ�.
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
		// �б�� ���Ⱑ ������ �ܼ�â�� ���۸� �����ϴ� �κ��̿���!
		// ���� ���۸������� �ܼ�â�� ���۰� 2�� �ʿ��մϴ�!
		HANDLE hOutputBuffer = ::CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
			0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);

		// ǥ�� ��� �ܼ�â�� ������ �����ϴ� �κ��̿���!
		::SetConsoleScreenBufferSize(hOutputBuffer, m_outputScreenBufferInfo.dwSize);
		::SetConsoleWindowInfo(hOutputBuffer, TRUE, &m_outputScreenBufferInfo.srWindow);
		::SetConsoleTextAttribute(hOutputBuffer, m_outputScreenBufferInfo.wAttributes);

		// ���� ������ �Ϸ�Ǿ����� �����ҰԿ�!
		m_arrOutputBuffer[i] = hOutputBuffer;
	}

	// ����Ʈ������ Ű���� Ŀ���� �����ϴ�.
	m_currentOutputBuffer = EConsoleOutputBufferType::FRONT;
	ShowCursor(false);

	// ������� Ű���� Ŀ���� �����ϴ�.
	m_currentOutputBuffer = EConsoleOutputBufferType::BACK;
	ShowCursor(false);

	return EReturnType::SUCCESS;
}

/*
	�����ߴ� ��� ���۵��� �����մϴ�.
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
	���� ��� ������ ��� ��ǥ�� �ű�ϴ�.
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
	�ܼ�â ����� �����մϴ�.
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
	�ܼ�â Ÿ��Ʋ�� �����մϴ�.
*/
void DoubleBufferingConsoleHandler::ChangeTitle(const Char* szTitle)
{
	::SetWindowText(m_hConsole, szTitle);
}

/*
	�ܼ�â ������ ������ �����մϴ�.
	���ڻ��� ���� �߿��� ������ �� �־��.
*/
EReturnType DoubleBufferingConsoleHandler::ChangeRenderingColor(EConsoleRenderingColor renderingColor, EConsoleRenderingType renderingType)
{
	if ((renderingColor < EConsoleRenderingColor::BLACK) ||
		(renderingColor > EConsoleRenderingColor::BRIGHT_WHITE))
	{
		return EReturnType::FAIL;
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
	�ܼ�â Ŀ�� ��� ���θ� �����մϴ�.
	���콺 Ŀ���� �ƴ϶� Ű���� Ŀ���� �ǹ��ؿ�.
*/
void DoubleBufferingConsoleHandler::ShowCursor(bool bShow)
{
	HANDLE hCurrentOutputBuffer = m_arrOutputBuffer[ToUnderlyingType(m_currentOutputBuffer)];
	RX_ASSERT(LogConsoleHandler, hCurrentOutputBuffer != nullptr);

	CONSOLE_CURSOR_INFO consoleCursorInfo; // Ŀ�� ������ CONSOLE_CURSOR_INFO�� �ֽ��ϴ�.
	::GetConsoleCursorInfo(hCurrentOutputBuffer, &consoleCursorInfo);

	consoleCursorInfo.bVisible = bShow;
	::SetConsoleCursorInfo(hCurrentOutputBuffer, &consoleCursorInfo);
}

/*
	���� ��� ���ۿ� ���ڵ��� ����մϴ�.
	����� �Ŀ��� �ݵ�� ���۸� ��ü�ؾ� �մϴ�.
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
	�ܼ�â�� ��µ� ��� �͵��� ����ϴ�.
	��� ������ ���� ������ �״�� �����մϴ�.
*/
EReturnType DoubleBufferingConsoleHandler::ClearScreen()
{
	// ���� X ���� = �簢�� ����
	Uint32 size = m_outputScreenBufferInfo.dwSize.X * m_outputScreenBufferInfo.dwSize.Y;

	// �ܼ�â�� ���۸� �������� ä��ϴ�.
	DWORD dwWrittenCount = 0;
	COORD beginPos = { 0, 0 };

	HANDLE hCurrentOutputBuffer = m_arrOutputBuffer[ToUnderlyingType(m_currentOutputBuffer)];
	RX_ASSERT(LogConsoleHandler, hCurrentOutputBuffer != nullptr);

	if (::FillConsoleOutputCharacter(hCurrentOutputBuffer, ' ', size, beginPos, &dwWrittenCount) == FALSE)
	{
		return EReturnType::FAIL;
	}

	// �ܼ�â ��� ���� �Ӽ��� ����� �κ��� ����ϴ�.
	if (::FillConsoleOutputAttribute(hCurrentOutputBuffer, defaultAttr, size, beginPos, &dwWrittenCount) == FALSE)
	{
		return EReturnType::FAIL;
	}

	MovePosition(beginPos.X, beginPos.Y); // Ŀ�� ��ġ�� ó������ �̵���ŵ�ϴ�.
	return EReturnType::SUCCESS;
}

/*
	�ܼ�â �Է� ���۸� ���ϴ�.
	�ܼ�â������ �Ϻ� ���ڰ� �Է� ���ۿ� ���� �� �����ϱ� �����ϼ���!
*/
void DoubleBufferingConsoleHandler::FlushInputBuffer()
{
	HANDLE hCurrentOutputBuffer = m_arrOutputBuffer[ToUnderlyingType(m_currentOutputBuffer)];
	RX_ASSERT(LogConsoleHandler, hCurrentOutputBuffer != nullptr);
	::FlushConsoleInputBuffer(hCurrentOutputBuffer);
}

/*
	�ܼ�â ��� ������ ������� �����ϴ�.
*/
void DoubleBufferingConsoleHandler::ResetRenderingColor()
{
	HANDLE hCurrentOutputBuffer = m_arrOutputBuffer[ToUnderlyingType(m_currentOutputBuffer)];
	RX_ASSERT(LogConsoleHandler, hCurrentOutputBuffer != nullptr);

	m_outputScreenBufferInfo.wAttributes = defaultAttr;
	::SetConsoleTextAttribute(hCurrentOutputBuffer, defaultAttr);
}

/*
	����ۿ� ����Ʈ���۸� ��ȯ�մϴ�.
*/
void DoubleBufferingConsoleHandler::FlipOutputBuffer()
{
	HANDLE hCurrentOutputBuffer = m_arrOutputBuffer[ToUnderlyingType(m_currentOutputBuffer)];
	RX_ASSERT(LogConsoleHandler, hCurrentOutputBuffer != nullptr);

	// ����ۿ� �������� ������ Ȱ��ȭ��Ű�� �κ�!
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
	������ �Է¹޽��ϴ�.
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
	�Ǽ��� �Է¹޽��ϴ�.
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
	���ڿ��� �Է¹޽��ϴ�.
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
	�ܼ�â Ŀ���� ���� ��ǥ�� �˷��ݴϴ�.
*/
COORD DoubleBufferingConsoleHandler::QueryCurrentPosition()
{
	HANDLE hCurrentOutputBuffer = m_arrOutputBuffer[ToUnderlyingType(m_currentOutputBuffer)];
	RX_ASSERT(LogConsoleHandler, hCurrentOutputBuffer != nullptr);

	::GetConsoleScreenBufferInfo(hCurrentOutputBuffer, &m_outputScreenBufferInfo);
	return m_outputScreenBufferInfo.dwCursorPosition;
}