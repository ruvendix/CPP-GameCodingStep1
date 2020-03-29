// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��ȭ ����Դϴ�.
// �б� ������ ����, ���� ��ȭ ����, ���� ��ȭ�� �����մϴ�.
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

	// ȭ��
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::YELLOW);
	PRINTF(x + 4, y + 2, m_spInfo->strSpeaker.c_str());

	// ���
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::AQUA);
	PRINTF(x + 6, y + 4, m_spInfo->strScript.c_str());

	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, currentConsoleOutputColor);
}

std::shared_ptr<DialogNode> DialogNode::FindNextNode() const
{
	return m_spNextNode;
}
