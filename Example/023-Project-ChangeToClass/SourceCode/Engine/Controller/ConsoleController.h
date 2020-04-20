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
#include "Element\ConsoleSelector.h"
#include "ConsoleControllerEnum.h"

using ArrConsoleDblBufferingHandle = std::array<HANDLE, common_func::ToUnderlyingType(EConsoleScreenBufferTypeIdx::MAX)>;

DECLARE_LOG_CATEGORY(ConsoleController);
class ConsoleController final
{
	DECLARE_PHOENIX_SINGLETON(ConsoleController);

public:
	void Initialize(const std::string_view& szTitle, const SizeInfo& sizeInfo);
	void Flipping();
	void Finalize();

	void PutString(Int32 x, Int32 y, const std::string_view& szOutput);
    void AdjustConsoleArea(Uint32 width, Uint32 height);
    void AdjustConsoleArea(const SizeInfo& sizeInfo);
    void DefaultConsoleGameStyle();
    void PauseGame();
    void ClearConsoleScreen();
    void ClearStdInputBuffer();
    void MoveConsolePos(Int32 x, Int32 y);
    void MoveConsolePos(const COORD& pos);
    void AlignCenter(const SizeInfo& areaSizeInfo, const SizeInfo& targetSizeInfo);
    void ChangeTitle(const std::string_view& szTitle);
	void ChangeConsoleOutputColor(EConsoleOutputType consoleOutputType, EConsoleOutputColorType consoleOutputColorType);
    void ShowConsoleCursor(bool bShow);
	void RestoreConsoleSelector();
	void PushBackupConsoleSelector();
	void AddSelectorPosX(Int32 x);
	void AddSelectorPosY(Int32 y);
	void DrawSelector() const;

	void ModifyCurrentConsoleSelectorPos(const COORD& pos);
	void ModifyCurrentConsoleSelectorPosX(Int32 x);
	void ModifyCurrentConsoleSelectorPosY(Int32 y);

	const COORD& QueryCurrentConsoleSelectorPos() const;
	COORD QueryCurrentConsolePos();
    EConsoleOutputColorType QueryCurrentConsoleOutputColor(EConsoleOutputType consoleOutputType) const;

	bool IsEmptySelector() const
	{
		return (m_stackConsoleSelector.empty() == true);
	}

    HANDLE getConsoleScreenBufferHandle(EConsoleScreenBufferTypeIdx consoleScreenBufferType) const
    {
		return m_hConsoleScreenBuffers.at(common_func::ToUnderlyingType(consoleScreenBufferType));
    }

	HANDLE getCurrentConsoleScreenBufferHandle() const
	{
		return getConsoleScreenBufferHandle(m_currentConsoleScreenBufferType);
	}

	ConsoleSelector& getCurrentConsoleSelector() const
	{
		return *m_pCurrentConsoleSelector;
	}

private:
	ArrConsoleDblBufferingHandle m_hConsoleScreenBuffers;
	CONSOLE_SCREEN_BUFFER_INFO m_consoleScreenBufferInfo;
	EConsoleScreenBufferTypeIdx m_currentConsoleScreenBufferType = EConsoleScreenBufferTypeIdx::FRONT;

    ConsoleSelector* m_pCurrentConsoleSelector = nullptr; // 백업이 필요할 때는 스마트 포인터를 사용하지 않아요!
	std::stack<std::unique_ptr<ConsoleSelector>> m_stackConsoleSelector;
};

#endif