// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 기능이 없는 콘솔 핸들러입니다.
// 콘솔 핸들러가 초기화되지 않았을 때 사용됩니다.
// FIND_SUBSYSTEM() 매크로를 통해서만 사용됩니다.
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