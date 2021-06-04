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

class ConsoleHandlerInside final
{
public:
	ConsoleHandlerInside() = default;
	~ConsoleHandlerInside() = default;

	void SetUp();
	void MovePosition(Int32 x, Int32 y);
	void AdjustSize(Uint32 width, Uint32 height);
	void ChangeTitle(const Char* szTitle);
	void ChangeRenderingColor(EConsoleRenderingColor renderingColor, EConsoleRenderingType renderingType);
	void ShowCursor(bool bShow);
	void ClearScreen();
	void FlushInputBuffer();
	void ResetRenderingColor();

	COORD QueryCurrentPosition();

private:
	Uint32 m_defaultOutputAttr = 0; // �⺻ ��� �Ӽ��Դϴ�.
	HWND m_hConsole = nullptr; // �ܼ�â�� �ڵ��Դϴ�.
	HANDLE m_hStdInput = nullptr; // ǥ�� �Է� ������ �ڵ��Դϴ�.
	HANDLE m_hStdOutput = nullptr; // ǥ�� ��� ������ �ڵ��Դϴ�.
	CONSOLE_SCREEN_BUFFER_INFO m_outputScreenBufferInfo; // ��� ���� �����Դϴ�.
};

void ConsoleHandlerInside::SetUp()
{
	m_hConsole = ::GetConsoleWindow();
	RX_ASSERT(LogConsoleHandler, m_hConsole != nullptr);

	m_hStdInput = ::GetStdHandle(STD_INPUT_HANDLE);
	RX_ASSERT(LogConsoleHandler, m_hStdInput != nullptr);

	m_hStdOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
	RX_ASSERT(LogConsoleHandler, m_hStdOutput != nullptr);

	::GetConsoleScreenBufferInfo(m_hStdOutput, &m_outputScreenBufferInfo);
	m_defaultOutputAttr = m_outputScreenBufferInfo.wAttributes;

	ChangeTitle("Default");
	AdjustSize(60, 30);
}

void ConsoleHandlerInside::MovePosition(Int32 x, Int32 y)
{
	COORD pos;
	pos.X = static_cast<Int16>(x);
	pos.Y = static_cast<Int16>(y);

	::SetConsoleCursorPosition(m_hStdOutput, pos);
}

void ConsoleHandlerInside::AdjustSize(Uint32 width, Uint32 height)
{
	Char buffer[DEFAULT_CHAR_BUFFER_SIZE];
	::ZeroMemory(buffer, DEFAULT_CHAR_BUFFER_SIZE);

	sprintf_s(buffer, DEFAULT_CHAR_BUFFER_SIZE, "mode con cols=%d lines=%d", width, height);
	std::system(buffer);

	m_outputScreenBufferInfo.dwSize.X = static_cast<Uint16>(width);
	m_outputScreenBufferInfo.dwSize.Y = static_cast<Uint16>(height);
}

void ConsoleHandlerInside::ChangeTitle(const Char* szTitle)
{
	::SetWindowText(m_hConsole, szTitle);
}

void ConsoleHandlerInside::ChangeRenderingColor(EConsoleRenderingColor renderingColor, EConsoleRenderingType renderingType)
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

void ConsoleHandlerInside::ShowCursor(bool bShow)
{
	CONSOLE_CURSOR_INFO consoleCursorInfo; // Ŀ�� ������ CONSOLE_CURSOR_INFO�� �ֽ��ϴ�.
	::GetConsoleCursorInfo(m_hStdOutput, &consoleCursorInfo);

	consoleCursorInfo.bVisible = bShow;
	::SetConsoleCursorInfo(m_hStdOutput, &consoleCursorInfo);
}

void ConsoleHandlerInside::ClearScreen()
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
	if (::FillConsoleOutputAttribute(m_hStdOutput, m_defaultOutputAttr, size, beginPos, &dwWrittenCnt) == FALSE)
	{
		RX_ERROR(LogConsoleHandler, EErrorCode::FAILED_CLEAR_SCREEN);
	}

	MovePosition(beginPos.X, beginPos.Y); // Ŀ�� ��ġ�� ó������ �̵���ŵ�ϴ�.	
}

void ConsoleHandlerInside::FlushInputBuffer()
{
	::FlushConsoleInputBuffer(m_hStdInput);
}

void ConsoleHandlerInside::ResetRenderingColor()
{
	m_outputScreenBufferInfo.wAttributes = m_defaultOutputAttr;
	::SetConsoleTextAttribute(m_hStdOutput, m_defaultOutputAttr);
}

COORD ConsoleHandlerInside::QueryCurrentPosition()
{
	::GetConsoleScreenBufferInfo(m_hStdOutput, &m_outputScreenBufferInfo);
	return m_outputScreenBufferInfo.dwCursorPosition;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
ConsoleHandler::ConsoleHandler()
{
	m_spInside = std::make_unique<ConsoleHandlerInside>();
}

/*
	�ܼ�â�� �ʱ�ȭ�մϴ�.
	�ܼ�â �̸��� ������ ������ �����ؿ�.
	�ڵ鵵 ���⿡�� �����մϴ�.
*/
void ConsoleHandler::SetUp()
{
	m_spInside->SetUp();
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
	m_spInside->MovePosition(x, y);
}

/*
	�ܼ�â ����� �����մϴ�.
*/
void ConsoleHandler::AdjustSize(Uint32 width, Uint32 height)
{
	m_spInside->AdjustSize(width, height);
}

/*
	�ܼ�â Ÿ��Ʋ�� �����մϴ�.
*/
void ConsoleHandler::ChangeTitle(const Char* szTitle)
{
	m_spInside->ChangeTitle(szTitle);
}

/*
	�ܼ�â ������ ������ �����մϴ�.
	���ڻ��� ���� �߿��� ������ �� �־��.
*/
void ConsoleHandler::ChangeRenderingColor(EConsoleRenderingColor renderingColor, EConsoleRenderingType renderingType)
{
	m_spInside->ChangeRenderingColor(renderingColor, renderingType);
}

/*
	�ܼ�â Ŀ�� ��� ���θ� �����մϴ�.
	���콺 Ŀ���� �ƴ϶� Ű���� Ŀ���� �ǹ��ؿ�.
*/
void ConsoleHandler::ShowCursor(bool bShow)
{
	m_spInside->ShowCursor(bShow);
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
	m_spInside->ClearScreen();
}

/*
	�ܼ�â �Է� ���۸� ���ϴ�.
	�ܼ�â������ �Ϻ� ���ڰ� �Է� ���ۿ� ���� �� �����ϱ� �����ϼ���!
*/
void ConsoleHandler::FlushInputBuffer()
{
	m_spInside->FlushInputBuffer();
}

/*
	�ܼ�â ��� ������ ������� �����ϴ�.
*/
void ConsoleHandler::ResetRenderingColor()
{
	m_spInside->ResetRenderingColor();
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
void ConsoleHandler::InputString(OUT std::string& str)
{
	Char buffer[DEFAULT_CHAR_BUFFER_SIZE];
	::ZeroMemory(buffer, DEFAULT_CHAR_BUFFER_SIZE);
	scanf_s("%[^\n]s", buffer, DEFAULT_CHAR_BUFFER_SIZE);
	FlushInputBuffer();
	str.assign(buffer);
}

/*
	�ܼ�â Ŀ���� ���� ��ǥ�� �˷��ݴϴ�.
*/
COORD ConsoleHandler::QueryCurrentPosition()
{
	return m_spInside->QueryCurrentPosition();
}