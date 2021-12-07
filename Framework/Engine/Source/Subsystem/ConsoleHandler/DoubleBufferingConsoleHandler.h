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
#include "Base/IConsoleHandler.h"

// ���� ����
class DoubleBufferingConsoleHandlerInside;

class DoubleBufferingConsoleHandler final : public IConsoleHandler
{
	ONLY_SUBSYSTEM_CTOR(DoubleBufferingConsoleHandler);

public:
	virtual void StartUp() override;
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
	virtual void Pause() const override;

	virtual Int32 InputInteger() override;
	virtual Float InputFloat() override;
	virtual void InputString(OUT std::string& str) override;

	virtual COORD QueryCurrentPosition() override;
	virtual Bool CheckValidCurrentOutputBuffer() override;

private:
	std::unique_ptr<DoubleBufferingConsoleHandlerInside> m_spInside = nullptr;
};