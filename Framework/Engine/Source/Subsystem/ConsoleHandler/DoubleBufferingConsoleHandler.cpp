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
	Uint32 m_defaultOutputAttr = 0; // �⺻ ��� �Ӽ��Դϴ�.
	HWND m_hConsole = nullptr; // �ܼ�â�� �ڵ��Դϴ�.
	HANDLE m_hStdInput = nullptr; // ǥ�� �Է� ������ �ڵ��Դϴ�.(�Է� ���۴� �ϳ�!)
	CONSOLE_SCREEN_BUFFER_INFO m_outputScreenBufferInfo; // ��� ���� �����Դϴ�.
	EnumIdx::ConsoleOutputBuffer::Data m_currentOutputBufferIdx = EnumIdx::ConsoleOutputBuffer::FRONT; // ���� ȭ�鿡 ���̴� ��� �����Դϴ�.
	std::array<HANDLE, EnumIdx::ConsoleOutputBuffer::COUNT> m_outputBufferHandles; // ��� ���� �ڵ� �迭�Դϴ�.
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
		// �б�� ���Ⱑ ������ �ܼ�â�� ���۸� �����ϴ� �κ��̿���!
		// ���� ���۸������� �ܼ�â�� ���۰� 2�� �ʿ��մϴ�!
		HANDLE hOutputBuffer = ::CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);

		// ǥ�� ��� �ܼ�â�� ������ �����ϴ� �κ��̿���!
		::SetConsoleScreenBufferSize(hOutputBuffer, m_outputScreenBufferInfo.dwSize);
		::SetConsoleWindowInfo(hOutputBuffer, TRUE, &m_outputScreenBufferInfo.srWindow);
		::SetConsoleTextAttribute(hOutputBuffer, m_outputScreenBufferInfo.wAttributes);

		// ���� ������ �Ϸ�Ǿ����� �����ҰԿ�!
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

	// ���� ������� �ٸ��� ���� â ������� 1�� ����� �մϴ�.
	// ȭ�� ��ǥ�� 0���� �����ϹǷ� ���̰� 40�̶�� 0 ~ 39�����ϱ��.
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

	CONSOLE_CURSOR_INFO consoleCursorInfo; // Ŀ�� ������ CONSOLE_CURSOR_INFO�� �ֽ��ϴ�.
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
	// ���� X ���� = �簢�� ����
	Uint32 size = m_outputScreenBufferInfo.dwSize.X * m_outputScreenBufferInfo.dwSize.Y;

	// �ܼ�â�� ���۸� �������� ä��ϴ�.
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

	// �ܼ�â ��� ���� �Ӽ��� ����� �κ��� ����ϴ�.
	if (::FillConsoleOutputAttribute(hCurrentOutputBuffer, m_defaultOutputAttr, size, beginPos, &dwWrittenCount) == FALSE)
	{
		RX_ERROR(LogConsoleHandler, EErrorCode::CLEAR_SCREEN_FAIL);
	}

	MovePosition(beginPos.X, beginPos.Y); // Ŀ�� ��ġ�� ó������ �̵���ŵ�ϴ�.
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

	// ����ۿ� �������� ������ Ȱ��ȭ��Ű�� �κ�!
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
	�ܼ�â�� �ʱ�ȭ�մϴ�.
	�ܼ�â �̸��� ������ ������ �����ؿ�.
	�ڵ鵵 ���⿡�� �����մϴ�.
	���� ���۸��� ���� ��� ���۸� �����ϰ� �����մϴ�.
*/
void DoubleBufferingConsoleHandler::SetUp()
{
	m_spInside->SetUp();
}

/*
	�����ߴ� ��� ���۵��� �����մϴ�.
*/
void DoubleBufferingConsoleHandler::CleanUp()
{
	m_spInside->CleanUp();
}

/*
	���� ��� ������ ��� ��ǥ�� �ű�ϴ�.
*/
void DoubleBufferingConsoleHandler::MovePosition(Int32 x, Int32 y)
{
	m_spInside->MovePosition(x, y);
}

/*
	�ܼ�â ����� �����մϴ�.
*/
void DoubleBufferingConsoleHandler::AdjustSize(Uint32 width, Uint32 height)
{
	m_spInside->AdjustSize(width, height);
}

/*
	�ܼ�â Ÿ��Ʋ�� �����մϴ�.
*/
void DoubleBufferingConsoleHandler::ChangeTitle(const Char* szTitle)
{
	m_spInside->ChangeTitle(szTitle);
}

/*
	�ܼ�â ������ ������ �����մϴ�.
	���ڻ��� ���� �߿��� ������ �� �־��.
*/
void DoubleBufferingConsoleHandler::ChangeRenderingColor(EConsoleRenderingColor renderingColor, EConsoleRenderingType renderingType)
{
	m_spInside->ChangeRenderingColor(renderingColor, renderingType);
}

/*
	�ܼ�â Ŀ�� ��� ���θ� �����մϴ�.
	���콺 Ŀ���� �ƴ϶� Ű���� Ŀ���� �ǹ��ؿ�.
*/
void DoubleBufferingConsoleHandler::ShowCursor(bool bShow)
{
	m_spInside->ShowCursor(bShow);
}

/*
	���� ��� ���ۿ� ���ڵ��� ����մϴ�.
	����� �Ŀ��� �ݵ�� ���۸� ��ü�ؾ� �մϴ�.
*/
void DoubleBufferingConsoleHandler::RenderString(Int32 x, Int32 y, const Char* szText)
{
	m_spInside->RenderString(x, y, szText);
}

/*
	�ܼ�â�� ��µ� ��� �͵��� ����ϴ�.
	��� ������ ���� ������ �״�� �����մϴ�.
*/
void DoubleBufferingConsoleHandler::ClearScreen()
{
	m_spInside->ClearScreen();
}

/*
	�ܼ�â �Է� ���۸� ���ϴ�.
	�ܼ�â������ �Ϻ� ���ڰ� �Է� ���ۿ� ���� �� �����ϱ� �����ϼ���!
*/
void DoubleBufferingConsoleHandler::FlushInputBuffer()
{
	m_spInside->FlushInputBuffer();
}

/*
	�ܼ�â ��� ������ ������� �����ϴ�.
*/
void DoubleBufferingConsoleHandler::ResetRenderingColor()
{
	m_spInside->ResetRenderingColor();
}

/*
	����ۿ� ����Ʈ���۸� ��ȯ�մϴ�.
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
	�ܼ�â Ŀ���� ���� ��ǥ�� �˷��ݴϴ�.
*/
COORD DoubleBufferingConsoleHandler::QueryCurrentPosition()
{
	return m_spInside->QueryCurrentPosition();
}

/*
	���� ��� ���۰� ��ȿ���� Ȯ���մϴ�.
*/
Bool DoubleBufferingConsoleHandler::CheckValidCurrentOutputBuffer()
{
	return (m_spInside->CheckValidCurrentOutputBuffer());
}