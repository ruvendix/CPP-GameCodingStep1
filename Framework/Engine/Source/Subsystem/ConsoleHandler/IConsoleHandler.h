// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ܼ� ������ �������̽��Դϴ�.
// =====================================================================================
#pragma once

#include "Subsystem/ISubsytem.h"
#include "ConsoleEnum.h"

class IConsoleHandler : public ISubsystem
{
	GENERATE_SUBSYSTEM_TYPE(ESubsystemType::CONSOLE_HANDLER);

public:
	IConsoleHandler() = default;
	virtual ~IConsoleHandler() = default;

	virtual void SetUp() override EMPTY_FUNC;
	virtual void CleanUp() override EMPTY_FUNC;

	virtual void ChangeRenderingColor(EConsoleRenderingColor renderingColor, EConsoleRenderingType renderingType) PURE_FUNC;
	virtual void ClearScreen() PURE_FUNC;

	virtual void MovePosition(Int32 x, Int32 y) PURE_FUNC;
	virtual void AdjustSize(Uint32 width, Uint32 height) PURE_FUNC;
	virtual void ChangeTitle(const Char* szTitle) PURE_FUNC;
	virtual void ShowCursor(bool bShow) PURE_FUNC;
	virtual void RenderString(Int32 x, Int32 y, const Char* szText) PURE_FUNC;
	virtual void FlushInputBuffer() PURE_FUNC;
	virtual void ResetRenderingColor() PURE_FUNC;
	virtual void FlipOutputBuffer() PURE_FUNC;
	virtual void Pause() const PURE_FUNC;

	virtual Int32 InputInteger() PURE_FUNC;
	virtual Float InputFloat() PURE_FUNC;
	virtual void InputString(OUT std::string& str) PURE_FUNC;

	virtual COORD QueryCurrentPosition() PURE_FUNC;
};