// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ܼ�â�� ���� �Ӽ��� �����ϴ� ��Ʈ�ѷ��Դϴ�.
// ���� ���۸��� ACTIVATION_CONSOLE_DBL_BUFFERING�� ��ó���⿡ �߰��ؾ� �۵��˴ϴ�.
// =====================================================================================

#include "PCH.h"
#include "ConsoleController.h"

#include "Context\ConfigContext.h"

DEFINE_LOG_CATEGORY(ConsoleController);
DEFINE_PHOENIX_SINGLETON(ConsoleController);

/*
�ܼ�â�� �ʱ�ȭ�մϴ�.
ACTIVATION_CONSOLE_DBL_BUFFERING�� Ȱ��ȭ�� ���¶�� ���� ���۸� ���� �۾��� ó���մϴ�.
*/
void ConsoleController::Initialize(const std::string_view& szTitle, const SizeInfo& sizeInfo)
{
	ConsoleController::I()->ChangeTitle(szTitle);
	ConsoleController::I()->AdjustConsoleArea(sizeInfo);
	ConsoleController::I()->DefaultConsoleGameStyle();

#ifdef ACTIVATION_CONSOLE_DBL_BUFFERING
	// ǥ�� ��� �ܼ�â�� ���� ������ �������� �κ��̿���!
	::ZeroMemory(&m_consoleScreenBufferInfo, sizeof(m_consoleScreenBufferInfo));
	::GetConsoleScreenBufferInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &m_consoleScreenBufferInfo);

	// ǥ�� ��� �ܼ�â�� Ŀ�� ������ �������� �κ��̿���!
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	::ZeroMemory(&consoleCursorInfo, sizeof(consoleCursorInfo));
	::GetConsoleCursorInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);

	for (Int32 i = 0; i < CommonFunc::ToUnderlyingType(EConsoleScreenBufferTypeIdx::MAX); ++i)
	{
		// �б�� ���Ⱑ ������ �ܼ�â�� ���۸� �����ϴ� �κ��̿���!
		// ���� ���۸������� �ܼ�â�� ���۰� 2�� �ʿ��մϴ�!
		HANDLE hConsoleScreenBuffer =
			::CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);

		// ǥ�� ��� �ܼ�â�� ������ �����ϴ� �κ��̿���!
		::SetConsoleScreenBufferSize(hConsoleScreenBuffer, m_consoleScreenBufferInfo.dwSize);
		::SetConsoleWindowInfo(hConsoleScreenBuffer, TRUE, &m_consoleScreenBufferInfo.srWindow);
		::SetConsoleTextAttribute(hConsoleScreenBuffer, m_consoleScreenBufferInfo.wAttributes);
		::SetConsoleCursorInfo(hConsoleScreenBuffer, &consoleCursorInfo);

		// ���� ������ �Ϸ�Ǿ����� �����ҰԿ�!
		m_hConsoleScreenBuffers[i] = hConsoleScreenBuffer;
	}

	m_currentConsoleScreenBufferType = EConsoleScreenBufferTypeIdx::BACK;
#else
	m_hConsoleScreenBuffers[CommonFunc::ToUnderlyingType(EConsoleScreenBufferType::FRONT)] = ::GetStdHandle(STD_OUTPUT_HANDLE);
#endif

	// ǥ�� �Է� �ܼ�â�� "Ctrl + C" ��ȿ�� "���콺 �Է� ����"�� �߰��ҰԿ�!
	DWORD dwMode = 0;
	::GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &dwMode);
	::SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), dwMode | ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	// Ŀ���� ǥ������ �����Կ�!
	ShowConsoleCursor(false);

	m_pCurrentConsoleSelector = trace_new ConsoleSelector;
}

/*
����Ʈ���۰� Ȱ��ȭ�Ǿ������� ����۷�,
����۰� Ȱ��ȭ�Ǿ������� ����Ʈ���۷� �����մϴ�.
*/
void ConsoleController::Flipping()
{
	// ���ۿ� �������� ������ Ȱ��ȭ��Ű�� �κ�!
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
�ܼ�â�� �ڵ��� �ݽ��ϴ�.
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
�ܼ�â�� ���ڿ��� ����մϴ�.
���� ���۸��� ���, Ȱ��ȭ���� ���� ���ۿ� ���ڿ��� ����մϴ�.
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
�ܼ�â�� ������ �����մϴ�.
*/
void ConsoleController::AdjustConsoleArea(Uint32 width, Uint32 height)
{
	std::string strConsoleProperty = CommonFunc::MakeFormatString("mode con cols=%d lines=%d", width, height);
	system(strConsoleProperty.c_str());

	ConfigCtx::I()->setResoultion(SizeInfo{ width, height });
}

/*
AdjustConsoleArea()�� SizeInfo �����ε��Դϴ�.
*/
void ConsoleController::AdjustConsoleArea(const SizeInfo& sizeInfo)
{
	AdjustConsoleArea(sizeInfo.width, sizeInfo.height);
}

/*
�ܼ�â�� ��Ÿ���� ���ӿ����� �����մϴ�.
�ִ�ȭ, �ּ�ȭ, �ݱ� ��ư�� ���� ������ �����˴ϴ�.
*/
void ConsoleController::DefaultConsoleGameStyle()
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
void ConsoleController::PauseGame()
{
	system("pause");
}

/*
�ܼ�â�� ��ü ������ �����ϰ� ����ϴ�.
���� : https://docs.microsoft.com/en-us/windows/console/clearing-the-screen
*/
void ConsoleController::ClearConsoleScreen()
{
#if 0
	system("cls"); // ����
#else
	HANDLE hConsoleScreenBuffer = getCurrentConsoleScreenBufferHandle();

	// ���� X ���� = �簢�� ����
	Uint32 consoleSize = m_consoleScreenBufferInfo.dwSize.X * m_consoleScreenBufferInfo.dwSize.Y;

	// �ܼ�â�� ���۸� �������� ä��ϴ�.
	DWORD dwWrittenCnt = 0;
	COORD beginConsolePos = { 0, 0 };
	if (::FillConsoleOutputCharacter(hConsoleScreenBuffer, ' ', consoleSize, beginConsolePos, &dwWrittenCnt) == FALSE)
	{
		return;
	}

	// �ܼ�â�� ���� �Ӽ��� �����մϴ�.
	if (::FillConsoleOutputAttribute(hConsoleScreenBuffer, m_consoleScreenBufferInfo.wAttributes, consoleSize, beginConsolePos, &dwWrittenCnt) == FALSE)
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
void ConsoleController::ClearStdInputBuffer()
{
	char value = '0'; // EOF�� '\n'�� �ƴϸ� �����ƿ�.

	// ǥ�� �Է� ���۸� ���� ����̿���.
	// std::fflush(stdin)�� ������, ǥ�ؿ��� �������� �ʾƼ� �����ҰԿ�.
	while ( (value != EOF) &&
		    (value != '\n') )
	{
		value = static_cast<char>(getchar());
	}
}

/*
�ܼ�â�� ��ǥ�� �̵���ŵ�ϴ�.
*/
void ConsoleController::MoveConsolePos(Int32 x, Int32 y)
{
	COORD pos{ static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(getCurrentConsoleScreenBufferHandle(), pos);
}

/*
MoveConsolePos()�� COORD �����ε��Դϴ�.
*/
void ConsoleController::MoveConsolePos(const COORD& pos)
{
	MoveConsolePos(pos.X, pos.Y);
}

/*
sizeInfo�� �̿��ؼ� �߾� �����մϴ�.
*/
void ConsoleController::AlignCenter(const SizeInfo& sizeInfo, Uint32 length)
{
	if (sizeInfo.width < length)
	{
		DEBUG_LOG("����� �۵������� ������������ ����...");
	}

	Int32 resultPosX = (sizeInfo.width / 2) - static_cast<Int32>((length / 2));
	MoveConsolePos(resultPosX, sizeInfo.height / 2);
}

/*
�ܼ�â�� Ÿ��Ʋ�� �����մϴ�.
*/
void ConsoleController::ChangeTitle(const std::string_view& szTitle)
{
	::SetWindowText(::GetConsoleWindow(), szTitle.data());
}

/*
�ܼ�â�� ��� ������ �����մϴ�.
���� ����� ��� ���� �� �� ���� �����մϴ�.
*/
void ConsoleController::ChangeConsoleOutputColor(EConsoleOutputType consoleOutputType, EConsoleOutputColorType consoleOutputColorType)
{
	if ( (consoleOutputColorType < EConsoleOutputColorType::BLACK) ||
		 (consoleOutputColorType > EConsoleOutputColorType::BRIGHT_WHITE) )
	{
		DEFAULT_ERROR_HANDLER(EErrorType::UNKNOWN_CONSOLE_COLOR);
		return;
	}

	// CONSOLE_SCREEN_BUFFER_INFO�� wAttributes�� ���� ������ �־��!
	// ���� 1����Ʈ���� ���� 4��Ʈ�� ��� ����, ���� 4��Ʈ�� ���� ������ �ǹ�����.
	// �� ������ ��Ʈ ������ �̿��ϸ� ��� ����� ���� ������ ���� �˾Ƴ� �� �ֽ��ϴ�!
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
�ܼ�â�� Ŀ�� ��� ���θ� �����մϴ�.
���콺 Ŀ���� �ƴ϶� Ű���� Ŀ���� �ǹ��մϴ�.
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
�ܼ�â�� ��ǥ�� �˷��ݴϴ�.
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
���� �ܼ� �ؽ�Ʈ ������ �˷��ݴϴ�.
*/
EConsoleOutputColorType ConsoleController::QueryCurrentConsoleOutputColor(EConsoleOutputType consoleOutputType) const
{
	// CONSOLE_SCREEN_BUFFER_INFO�� wAttributes�� ���� ������ �־��!
	// ���� 1����Ʈ���� ���� 4��Ʈ�� ��� ����, ���� 4��Ʈ�� ���� ������ �ǹ�����.
	// �� ������ ��Ʈ ������ �̿��ϸ� ��� ����� ���� ������ ���� �˾Ƴ� �� �ֽ��ϴ�!
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
