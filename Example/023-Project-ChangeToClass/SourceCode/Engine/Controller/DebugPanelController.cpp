// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 디버그 모드에서만 사용되는 패널입니다.
// FPS, 평균 FPS 등의 정보를 보여줍니다.
// =====================================================================================

#include "PCH.h"
#include "DebugPanelController.h"

#include "Context\ConfigContext.h"
#include "Controller\ConsoleController.h"
#include "Controller\FrameController.h"
#include "Controller\InputController.h"

class DebugPanelControllerHelper
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(DebugPanelControllerHelper);

public:
	static std::string_view ToStringFrameRate(EFrameRateType frameRateType);
};

std::string_view DebugPanelControllerHelper::ToStringFrameRate(EFrameRateType frameRateType)
{
	switch (frameRateType)
	{
		CASE_RETURN_STRING(EFrameRateType::CONSTANT, "CFR"); // 고정
		CASE_RETURN_STRING(EFrameRateType::VARIABLE_LIMITED, "Limited VFR"); // 제한 가변
		CASE_RETURN_STRING(EFrameRateType::VARIABLE_UNLIMITED, "Unlimited VFR"); // (무한 가변)
	}

	return "등록된 프레임 레이트가 아님!";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_PHOENIX_SINGLETON(DebugPanelController);

void DebugPanelController::Initialize()
{
	InputController::I()->InsertInputMappingInfo("FlipDebugPanel", VK_F1);
}

void DebugPanelController::PollInput()
{
	if (InputController::I()->CheckInputState("FlipDebugPanel", EInputMappingState::DOWN))
	{
		m_bShow = !m_bShow;
	}
}

void DebugPanelController::ShowContents(Int32 x, Int32 y)
{
	if (m_bShow == false)
	{
		return;
	}

	EConsoleOutputColorType currentConsoleOutputColor = ConsoleController::I()->QueryCurrentConsoleOutputColor(EConsoleOutputType::TEXT);

	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::YELLOW);
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::BACKGROUND, EConsoleOutputColorType::PURPLE);

	Int32 drawPosY = y;

	PUT_STRING(x, drawPosY, "Resolution(%d X %d)", ConfigCtx::I()->getResoultion().width, ConfigCtx::I()->getResoultion().height);
	++drawPosY;

	PUT_STRING(x, drawPosY, "FPS type(%s)", DebugPanelControllerHelper::ToStringFrameRate(FrameController::I()->getFrameRateType()).data());
	++drawPosY;

	PUT_STRING(x, drawPosY, "Input FPS(%d)", FrameController::I()->getInputFPS());
	++drawPosY;

	PUT_STRING(x, drawPosY, "FPS(%d)", FrameController::I()->getFPS());
	++drawPosY;

	PUT_STRING(x, drawPosY, "Avg FPS(%d)", FrameController::I()->getAvgFPS());
	++drawPosY;

	PUT_STRING(x, drawPosY, "DeltaTime(%f)", FrameController::I()->getDeltaTime());
	++drawPosY;

	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, currentConsoleOutputColor);
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::BACKGROUND, EConsoleOutputColorType::BLACK);
}