// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ܼ� �����Դϴ�.
// �ܼ�â�� �ٷ� �� ���˴ϴ�.
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
	HWND m_hConsole = nullptr; // �ܼ�â�� �ڵ��Դϴ�.
	HANDLE m_hStdInput = nullptr; // ǥ�� �Է� ������ �ڵ��Դϴ�.
	HANDLE m_hStdOutput = nullptr; // ǥ�� ��� ������ �ڵ��Դϴ�.
	CONSOLE_SCREEN_BUFFER_INFO m_outputScreenBufferInfo; // ��� ���� �����Դϴ�.
};