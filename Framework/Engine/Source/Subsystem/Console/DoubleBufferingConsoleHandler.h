// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ���۸��� �̿��ؼ� �ܼ�â�� �ٷ�ϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "Common/CommonType.h"
#include "IConsoleHandler.h"

class DoubleBufferingConsoleHandler final : public IConsoleHandler
{
public:
	DoubleBufferingConsoleHandler() = default;
	virtual ~DoubleBufferingConsoleHandler() = default;

	virtual void SetUp() override;
	virtual void CleanUp() override;
	virtual void ChangeRenderingColor(EConsoleRenderingColor renderingColor, EConsoleRenderingType renderingType) override;
	virtual void ClearScreen() override;

	virtual void MovePosition(Int32 x, Int32 y) override;
	virtual void AdjustSize(Uint32 width, Uint32 height) override;
	virtual void ChangeTitle(const Char* szTitle) override;
	virtual void ShowCursor(bool bShow) override;
	virtual void RenderString(Int32 x, Int32 y, const Char* szText) override;
	virtual void FlushInputBuffer() override;
	virtual void ResetRenderingColor() override;
	virtual void FlipOutputBuffer() override;

	virtual Int32 InputInteger() override;
	virtual Float InputFloat() override;
	virtual const Char* InputString() override;

	virtual COORD QueryCurrentPosition() override;

private:
	HWND m_hConsole = nullptr; // �ܼ�â�� �ڵ��Դϴ�.

	CONSOLE_SCREEN_BUFFER_INFO m_outputScreenBufferInfo; // ��� ���� �����Դϴ�.
	EConsoleOutputBufferType m_currentOutputBuffer = EConsoleOutputBufferType::FRONT; // ���� ȭ�鿡 ���̴� ��� �����Դϴ�.
	std::array<HANDLE, ToUnderlyingType(EConsoleOutputBufferType::COUNT)> m_arrOutputBuffer; // ��� ���� �迭�Դϴ�.
};