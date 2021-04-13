// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 콘솔 서비스의 인터페이스입니다.
// =====================================================================================
#pragma once

#include "Common/CommonEnum.h"
#include "Common/CommonInterface.h"
#include "ConsoleEnum.h"

class IConsoleHandler : public IDefault
{
public:
	virtual EReturnType SetUp() DEFAULT_FUNC
	virtual EReturnType CleanUp() DEFAULT_FUNC

	virtual EReturnType ChangeRenderingColor(EConsoleRenderingColor renderingColor, EConsoleRenderingType renderingType) = 0;
	virtual EReturnType ClearScreen() = 0;

	virtual void MovePosition(Int32 x, Int32 y) = 0;
	virtual void AdjustSize(Uint32 width, Uint32 height) = 0;
	virtual void ChangeTitle(const Char* szTitle) = 0;	
	virtual void ShowCursor(bool bShow) = 0;
	virtual void RenderString(Int32 x, Int32 y, const Char* szText) = 0;
	virtual void FlushInputBuffer() = 0;
	virtual void ResetRenderingColor() = 0;

	virtual Int32 InputInteger() = 0;
	virtual Float InputFloat() = 0;
	virtual const Char* InputString() = 0;

	virtual COORD QueryCurrentPosition() = 0;
};