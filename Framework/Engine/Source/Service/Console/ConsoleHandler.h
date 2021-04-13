// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 콘솔 서비스입니다.
// 콘솔창을 다룰 때 사용됩니다.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "Common/CommonType.h"
#include "IConsoleHandler.h"

class ConsoleHandler final : public IConsoleHandler
{
public:
	ConsoleHandler() = default;
	virtual ~ConsoleHandler() = default;

	virtual EReturnType SetUp() override;
	virtual EReturnType CleanUp() override;
	virtual EReturnType ChangeRenderingColor(EConsoleRenderingColor renderingColor, EConsoleRenderingType renderingType) override;
	virtual EReturnType ClearScreen() override;

	virtual void MovePosition(Int32 x, Int32 y) override;
	virtual void AdjustSize(Uint32 width, Uint32 height) override;
	virtual void ChangeTitle(const Char* szTitle) override;	
	virtual void ShowCursor(bool bShow) override;
	virtual void RenderString(Int32 x, Int32 y, const Char* szText) override;
	virtual void FlushInputBuffer() override;
	virtual void ResetRenderingColor() override;

	virtual Int32 InputInteger() override;
	virtual Float InputFloat() override;
	virtual const Char* InputString() override;

	virtual COORD QueryCurrentPosition() override;

private:
	HWND m_hConsole = nullptr; // 콘솔창의 핸들입니다.
	HANDLE m_hStdInput = nullptr; // 표준 입력 버퍼의 핸들입니다.
	HANDLE m_hStdOutput = nullptr; // 표준 출력 버퍼의 핸들입니다.
	CONSOLE_SCREEN_BUFFER_INFO m_outputScreenBufferInfo; // 출력 버퍼 정보입니다.
};