// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 콘솔창을 다룰 때 사용됩니다.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "Base/IConsoleHandler.h"

// 전방 선언
class ConsoleHandlerInside;

class ConsoleHandler final : public IConsoleHandler
{
	ONLY_SUBSYSTEM_CTOR(ConsoleHandler);

public:
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
	virtual void FlipOutputBuffer() OVERRIDE_EMPTY_FUNC;
	virtual void Pause() const override;

	virtual Int32 InputInteger() override;
	virtual Float InputFloat() override;
	virtual void InputString(OUT std::string& str) override;

	virtual COORD QueryCurrentPosition() override;
	virtual Bool CheckValidCurrentOutputBuffer() override;

private:
	std::unique_ptr<ConsoleHandlerInside> m_spInside = nullptr;
};