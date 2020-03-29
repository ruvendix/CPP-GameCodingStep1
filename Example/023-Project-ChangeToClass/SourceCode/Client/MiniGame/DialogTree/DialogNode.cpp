// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 대화 노드입니다.
// 분기 선택지 묶음, 연속 대화 묶음, 다음 대화를 포함합니다.
// =====================================================================================

#include "PCH.h"
#include "DialogNode.h"

#include "Controller\ConsoleController.h"

DialogNode::DialogNode(const std::string_view& szSpeaker, const std::string_view& szScript)
{
	m_spInfo = std::make_unique<DialogInfo>();
	m_spInfo->strSpeaker = szSpeaker;
	m_spInfo->strScript = szScript;
}

void DialogNode::Draw(Int32 x, Int32 y) const
{
	EConsoleOutputColorType currentConsoleOutputColor = ConsoleController::I()->QueryCurrentConsoleOutputColor(EConsoleOutputType::TEXT);

	// 화자
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::YELLOW);
	PRINTF(x + 4, y + 2, m_spInfo->strSpeaker.c_str());

	// 대사
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::AQUA);
	PRINTF(x + 6, y + 4, m_spInfo->strScript.c_str());

	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, currentConsoleOutputColor);
}

std::shared_ptr<DialogNode> DialogNode::FindNextNode() const
{
	return m_spNextNode;
}
