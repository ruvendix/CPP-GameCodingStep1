// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ����� ���� �ܼ� �ڵ鷯�Դϴ�.
// �ܼ� �ڵ鷯�� �ʱ�ȭ���� �ʾ��� �� ���˴ϴ�.
// FIND_SUBSYSTEM() ��ũ�θ� ���ؼ��� ���˴ϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "IConsoleHandler.h"

class IConsoleHandlerNull : public IConsoleHandler
{
public:
	virtual void StartUp() OVERRIDE_EMPTY_FUNC;
	virtual void CleanUp() OVERRIDE_EMPTY_FUNC;

	virtual void ChangeRenderingColor(EConsoleRenderingColor renderingColor, EConsoleRenderingType renderingType) OVERRIDE_EMPTY_FUNC;
	virtual void ClearScreen() OVERRIDE_EMPTY_FUNC;

	virtual void MovePosition(Int32 x, Int32 y) OVERRIDE_EMPTY_FUNC;
	virtual void AdjustSize(Uint32 width, Uint32 height) OVERRIDE_EMPTY_FUNC;
	virtual void ChangeTitle(const Char* szTitle) OVERRIDE_EMPTY_FUNC;
	virtual void ShowCursor(bool bShow) OVERRIDE_EMPTY_FUNC;
	virtual void RenderString(Int32 x, Int32 y, const Char* szText) OVERRIDE_EMPTY_FUNC;
	virtual void FlushInputBuffer() OVERRIDE_EMPTY_FUNC;
	virtual void ResetRenderingColor() OVERRIDE_EMPTY_FUNC;
	virtual void FlipOutputBuffer() OVERRIDE_EMPTY_FUNC;
	virtual void Pause() CONST_OVERRIDE_EMPTY_FUNC;

	virtual Int32 InputInteger() RETURN_FUNC(0);
	virtual Float InputFloat() RETURN_FUNC(0.0f);
	virtual void InputString(std::string& str) OVERRIDE_EMPTY_FUNC;

	virtual COORD QueryCurrentPosition() RETURN_FUNC(COORD());
	virtual Bool CheckValidCurrentOutputBuffer() RETURN_FUNC(true);
};