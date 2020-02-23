// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 콘솔창의 여러 속성을 제어하는 컨트롤러입니다.
// 더블 버퍼링은 ACTIVATION_CONSOLE_DBL_BUFFERING을 전처리기에 추가해야 작동됩니다.
// =====================================================================================

#ifndef CONSOLE_CONTROLLER__H__
#define CONSOLE_CONTROLLER__H__

#include "Common\CommonFunc.h"
#include "Element\NameTag.h"

DECLARE_LOG_CATEGORY(ConsoleController);

enum class EConsoleScreenBufferType : Int32
{
	FRONT = 0,
	BACK,
	MAX,
};

// 글자색과 배경색 둘 다 사용됩니다.
enum class EConsoleOutputColorType : Int32
{
	UNKNOWN = -1,
	BLACK,
	BLUE,
	GREEN,
	AQUA,
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_AQUA,
	LIGHT_RED,
	LIGHT_PURPLE,
	LIGHT_YELLOW,
	BRIGHT_WHITE,
};

enum class EConsoleOutputType : Int32
{
	TEXT = 0,
	BACKGROUND,
};

class ConsoleController
{
	DECLARE_SINGLETON(ConsoleController);

public:
	using ConsoleDblBufferingHandle = std::array<HANDLE, CommonFunc::ToUnderlyingType(EConsoleScreenBufferType::MAX)>;

	void Initialize(const std::string_view& szTitle, const SizeInfo& sizeInfo);
	void Flipping();
	void Finalize();

	void OutputStr(Int32 posX, Int32 posY, const std::string_view& szOutput);
    void AdjustConsoleArea(Uint32 width, Uint32 height);
    void AdjustConsoleArea(const SizeInfo& sizeInfo);
    void DefaultConsoleGameStyle();
    void PauseGame();
    void ClearConsoleScreen();
    void ClearStdInputBuffer();
    void MoveConsolePos(Int32 posX, Int32 posY);
    void MoveConsolePos(const COORD& pos);
    void AlignCenter(const SizeInfo& sizeInfo, Uint32 length);
    void ChangeTitle(const std::string_view& szTitle);
	void ChangeConsoleOutputColor(EConsoleOutputType consoleOutputType, EConsoleOutputColorType consoleOutputColorType);
    void ShowConsoleCursor(bool bShow);

    COORD GetCurrentConsolePos();
    EConsoleOutputColorType QueryCurrentConsoleOutputColor(EConsoleOutputType consoleOutputType);

    HANDLE getConsoleScreenBufferHandle(EConsoleScreenBufferType consoleScreenBufferType) const
    {
        HANDLE hConsoleScreenBuffer = m_hConsoleScreenBuffers[CommonFunc::ToUnderlyingType(consoleScreenBufferType)];
        CHECK_NULLPTR(hConsoleScreenBuffer);
        return hConsoleScreenBuffer;
    }

	HANDLE getCurrentConsoleScreenBufferHandle() const
	{
		return getConsoleScreenBufferHandle(m_currentConsoleScreenBufferType);
	}

private:
	ConsoleDblBufferingHandle m_hConsoleScreenBuffers;
	EConsoleScreenBufferType m_currentConsoleScreenBufferType = EConsoleScreenBufferType::FRONT;
};

#endif