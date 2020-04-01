// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ����� ��忡���� ���Ǵ� �г��Դϴ�.
// FPS, ��� FPS ���� ������ �����ݴϴ�.
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
		CASE_RETURN_STRING(EFrameRateType::CONSTANT, "CFR"); // ����
		CASE_RETURN_STRING(EFrameRateType::VARIABLE_LIMITED, "Limited VFR"); // ���� ����
		CASE_RETURN_STRING(EFrameRateType::VARIABLE_UNLIMITED, "Unlimited VFR"); // (���� ����)
	}

	return "��ϵ� ������ ����Ʈ�� �ƴ�!";
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