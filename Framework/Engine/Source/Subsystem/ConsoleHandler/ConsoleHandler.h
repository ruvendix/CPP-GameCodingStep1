// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ܼ�â�� �ٷ� �� ���˴ϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "Common/CommonType.h"
#include "IConsoleHandler.h"

class ConsoleHandler final : public IConsoleHandler
{
	ONLY_SUBSYSTEM(ConsoleHandler);

public:
	virtual void SetUp() override;
	virtual void CleanUp() override;
	virtual void ChangeRenderingColor(EConsoleRenderingColor eRenderingColor, EConsoleRenderingType eRenderingType) override;
	virtual void ClearScreen() override;

	virtual void MovePosition(Int32 x, Int32 y) override;
	virtual void AdjustSize(Uint32 width, Uint32 height) override;
	virtual void ChangeTitle(const Char* szTitle) override;	
	virtual void ShowCursor(bool bShow) override;
	virtual void RenderString(Int32 x, Int32 y, const Char* szText) override;
	virtual void FlushInputBuffer() override;
	virtual void ResetRenderingColor() override;
	virtual void FlipOutputBuffer() override { }
	virtual void Pause() const override;

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