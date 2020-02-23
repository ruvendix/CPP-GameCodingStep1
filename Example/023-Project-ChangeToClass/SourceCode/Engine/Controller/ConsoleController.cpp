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
DEFINE_SINGLETON(ConsoleController);

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
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	::ZeroMemory(&consoleScreenBufferInfo, sizeof(consoleScreenBufferInfo));
	::GetConsoleScreenBufferInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &consoleScreenBufferInfo);

	// ǥ�� ��� �ܼ�â�� Ŀ�� ������ �������� �κ��̿���!
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	::ZeroMemory(&consoleCursorInfo, sizeof(consoleCursorInfo));
	::GetConsoleCursorInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);

	for (Int32 i = 0; i < CommonFunc::ToUnderlyingType(EConsoleScreenBufferType::MAX); ++i)
	{
		// �б�� ���Ⱑ ������ �ܼ�â�� ���۸� �����ϴ� �κ��̿���!
		// ���� ���۸������� �ܼ�â�� ���۰� 2�� �ʿ��մϴ�!
		HANDLE hConsoleScreenBuffer =
			::CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);

		// ǥ�� ��� �ܼ�â�� ������ �����ϴ� �κ��̿���!
		::SetConsoleScreenBufferSize(hConsoleScreenBuffer, consoleScreenBufferInfo.dwSize);
		::SetConsoleWindowInfo(hConsoleScreenBuffer, TRUE, &consoleScreenBufferInfo.srWindow);
		::SetConsoleTextAttribute(hConsoleScreenBuffer, consoleScreenBufferInfo.wAttributes);
		::SetConsoleCursorInfo(hConsoleScreenBuffer, &consoleCursorInfo);

		// ���� ������ �Ϸ�Ǿ����� �����ҰԿ�!
		m_hConsoleScreenBuffers[i] = hConsoleScreenBuffer;
	}
#else
	m_hConsoleScreenBuffers[CommonFunc::ToUnderlyingType(EConsoleScreenBufferType::FRONT)] = ::GetStdHandle(STD_OUTPUT_HANDLE);
#endif

	// ǥ�� �Է� �ܼ�â�� "Ctrl + C" ��ȿ�� "���콺 �Է� ����"�� �߰��ҰԿ�!
	DWORD dwMode = 0;
	::GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &dwMode);
	::SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), dwMode | ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	// Ŀ���� ǥ������ �����Կ�!
	ShowConsoleCursor(false);
}

/*
����Ʈ���۰� Ȱ��ȭ�Ǿ������� ����۷�,
����۰� Ȱ��ȭ�Ǿ������� ����Ʈ���۷� �����մϴ�.
*/
void ConsoleController::Flipping()
{
	if (m_currentConsoleScreenBufferType == EConsoleScreenBufferType::FRONT)
	{
		m_currentConsoleScreenBufferType = EConsoleScreenBufferType::BACK;
	}
	else if (m_currentConsoleScreenBufferType == EConsoleScreenBufferType::BACK)
	{
		m_currentConsoleScreenBufferType = EConsoleScreenBufferType::FRONT;
	}
	else
	{
		DEBUG_LOG_CATEGORY(ConsoleController, "�� �� ���� ���ۿ���!");
		return;
	}

	::SetConsoleActiveScreenBuffer(getCurrentConsoleScreenBufferHandle());
}

/*
�ܼ�â�� �ڵ��� �ݽ��ϴ�.
*/
void ConsoleController::Finalize()
{
#ifdef ACTIVATION_CONSOLE_DBL_BUFFERING
	for (Int32 i = 0; i < CommonFunc::ToUnderlyingType(EConsoleScreenBufferType::MAX); ++i)
	{
		::CloseHandle(m_hConsoleScreenBuffers[i]);
	}
#else
	::CloseHandle(m_hConsoleScreenBuffers[CommonFunc::ToUnderlyingType(EConsoleScreenBufferType::FRONT)]);
#endif
}

/*
�ܼ�â�� ���ڿ��� ����մϴ�.
���� ���۸��� ���, Ȱ��ȭ���� ���� ���ۿ� ���ڿ��� ����մϴ�.
*/
void ConsoleController::OutputStr(Int32 posX, Int32 posY, const std::string_view& szOutput)
{
	DWORD dwWrittenCnt = 0;
	WriteConsoleOutputCharacter(getCurrentConsoleScreenBufferHandle(),
		szOutput.data(), szOutput.size(), COORD{ static_cast<SHORT>(posX), static_cast<SHORT>(posY) }, &dwWrittenCnt);
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

	// ���� �ܼ�â�� ������ �����ɴϴ�.
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	::ZeroMemory(&consoleScreenBufferInfo, sizeof(consoleScreenBufferInfo));
	if (::GetConsoleScreenBufferInfo(hConsoleScreenBuffer, &consoleScreenBufferInfo) == FALSE)
	{
		return;
	}

	// ���� X ���� = �簢�� ����
	Uint32 consoleSize = consoleScreenBufferInfo.dwSize.X * consoleScreenBufferInfo.dwSize.Y;

	// �ܼ�â�� ���۸� �������� ä��ϴ�.
	DWORD dwWrittenCnt = 0;
	COORD beginConsolePos = { 0, 0 };
	if (::FillConsoleOutputCharacter(hConsoleScreenBuffer, ' ', consoleSize, beginConsolePos, &dwWrittenCnt) == FALSE)
	{
		return;
	}

	// �ܼ�â�� ���� �Ӽ��� �����մϴ�.
	if (::FillConsoleOutputAttribute(hConsoleScreenBuffer, consoleScreenBufferInfo.wAttributes,
			consoleSize, beginConsolePos, &dwWrittenCnt) == FALSE)
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
�ܼ�â�� ��ǥ�� �̵���ŵ�ϴ�.
*/
void ConsoleController::MoveConsolePos(Int32 posX, Int32 posY)
{
	COORD pos{ static_cast<SHORT>(posX), static_cast<SHORT>(posY) };
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
		DEBUG_LOG_CATEGORY(ConsoleController, "�����Ǵ� ���� ������ �ʰ��߾��!\n");
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	::ZeroMemory(&consoleScreenBufferInfo, sizeof(consoleScreenBufferInfo));

	HANDLE hConsoleScreenBuffer = getCurrentConsoleScreenBufferHandle();
	::GetConsoleScreenBufferInfo(hConsoleScreenBuffer, &consoleScreenBufferInfo);

	// CONSOLE_SCREEN_BUFFER_INFO�� wAttributes�� ���� ������ �־��!
	// ���� 1����Ʈ���� ���� 4��Ʈ�� ��� ����, ���� 4��Ʈ�� ���� ������ �ǹ�����.
	// �� ������ ��Ʈ ������ �̿��ϸ� ��� ����� ���� ������ ���� �˾Ƴ� �� �ֽ��ϴ�!
	WORD consoleScreenBufferAttr = 0;
	if (consoleOutputType == EConsoleOutputType::TEXT)
	{
		consoleScreenBufferAttr = consoleScreenBufferInfo.wAttributes & 0xFFF0;
		consoleScreenBufferAttr |= static_cast<BYTE>(consoleOutputColorType);
	}
	else if (consoleOutputType == EConsoleOutputType::BACKGROUND)
	{
		consoleScreenBufferAttr = consoleScreenBufferInfo.wAttributes & 0xFF0F;
		consoleScreenBufferAttr |= (static_cast<BYTE>(consoleOutputColorType) << 4);
	}
	else
	{
		DEBUG_LOG_CATEGORY(ConsoleController, "�� �� ���� ��� Ÿ���̿���!");
	}

	::SetConsoleTextAttribute(hConsoleScreenBuffer, consoleScreenBufferAttr);

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

	HANDLE hConsoleScreenBuffer = getCurrentConsoleScreenBufferHandle();
	::GetConsoleCursorInfo(hConsoleScreenBuffer, &consoleCursorInfo);

	consoleCursorInfo.bVisible = bShow;
	::SetConsoleCursorInfo(hConsoleScreenBuffer, &consoleCursorInfo);
}

/*
�ܼ�â�� ��ǥ�� �˷��ݴϴ�.
*/
COORD ConsoleController::GetCurrentConsolePos()
{
	COORD pos{ 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	::ZeroMemory(&consoleScreenBufferInfo, sizeof(consoleScreenBufferInfo));

	::GetConsoleScreenBufferInfo(getCurrentConsoleScreenBufferHandle(), &consoleScreenBufferInfo);
	pos.X = consoleScreenBufferInfo.dwCursorPosition.X;
	pos.Y = consoleScreenBufferInfo.dwCursorPosition.Y;

	return pos;
}

/*
���� �ܼ� �ؽ�Ʈ ������ �˷��ݴϴ�.
*/
EConsoleOutputColorType ConsoleController::QueryCurrentConsoleOutputColor(EConsoleOutputType consoleOutputType)
{
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	::ZeroMemory(&consoleScreenBufferInfo, sizeof(consoleScreenBufferInfo));

	::GetConsoleScreenBufferInfo(getCurrentConsoleScreenBufferHandle(), &consoleScreenBufferInfo);

	// CONSOLE_SCREEN_BUFFER_INFO�� wAttributes�� ���� ������ �־��!
	// ���� 1����Ʈ���� ���� 4��Ʈ�� ��� ����, ���� 4��Ʈ�� ���� ������ �ǹ�����.
	// �� ������ ��Ʈ ������ �̿��ϸ� ��� ����� ���� ������ ���� �˾Ƴ� �� �ֽ��ϴ�!
	BYTE consoleColorVal = 0;
	if (consoleOutputType == EConsoleOutputType::TEXT)
	{
		consoleColorVal = static_cast<BYTE>(consoleScreenBufferInfo.wAttributes & 0x000F);
	}
	else if (consoleOutputType == EConsoleOutputType::BACKGROUND)
	{
		consoleColorVal = static_cast<BYTE>((consoleScreenBufferInfo.wAttributes & 0x00F0) >> 4);
	}
	else
	{
		DEBUG_LOG_CATEGORY(ConsoleController, "�� �� ���� ��� Ÿ���̿���!");
	}


	if ( (consoleColorVal < static_cast<INT32>(EConsoleOutputColorType::BLACK)) ||
		 (consoleColorVal > static_cast<INT32>(EConsoleOutputColorType::BRIGHT_WHITE)) )
	{
		DEBUG_LOG_CATEGORY(ConsoleController, "�����Ǵ� ���� ������ �ʰ��߾��!\n");
		return EConsoleOutputColorType::UNKNOWN;
	}

	return static_cast<EConsoleOutputColorType>(consoleColorVal);
}
