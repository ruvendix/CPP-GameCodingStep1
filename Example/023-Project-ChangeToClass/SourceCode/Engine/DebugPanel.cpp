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
#include "DebugPanel.h"

#include "Context\ConfigContext.h"
#include "Controller\ConsoleController.h"
#include "Controller\FrameController.h"
#include "Controller\InputController.h"

class DebugPanelHelper
{
	NON_COPYABLE_ONLY_PRIVATE_CLASS(DebugPanelHelper);

public:
	static std::string_view ToStringFrameRate(EFrameRateType frameRateType);
};

std::string_view DebugPanelHelper::ToStringFrameRate(EFrameRateType frameRateType)
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

DEFINE_PHOENIX_SINGLETON(DebugPanel);

void DebugPanel::Initialize()
{
	InputController::I()->InsertInputMappingInfo("FlipDebugPanel", VK_F1);
}

void DebugPanel::ShowContents(Int32 posX, Int32 posY)
{
	if (InputController::I()->CheckInputState("FlipDebugPanel", EInputMappingState::DOWN))
	{
		m_bShow = !m_bShow;
	}

	if (m_bShow == false)
	{
		return;
	}

	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::YELLOW);
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::BACKGROUND, EConsoleOutputColorType::PURPLE);

	Int32 drawPosY = posY;

	PRINTF(posX, drawPosY, "Resolution(%d X %d)", ConfigCtx::I()->getResoultion().width, ConfigCtx::I()->getResoultion().height);
	++drawPosY;

	PRINTF(posX, drawPosY, "FPS type(%s)", DebugPanelHelper::ToStringFrameRate(FrameController::I()->getFrameRateType()));
	++drawPosY;

	PRINTF(posX, drawPosY, "FPS(%d)", FrameController::I()->getFPS());
	++drawPosY;

	PRINTF(posX, drawPosY, "Avg FPS(%d)", FrameController::I()->getAvgFPS());
	++drawPosY;

	PRINTF(posX, drawPosY, "DeltaTime(%f)", FrameController::I()->getDeltaTime());
	++drawPosY;

	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::BLACK);
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::BACKGROUND, EConsoleOutputColorType::BLACK);
}