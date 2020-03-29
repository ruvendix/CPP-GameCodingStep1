// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �б� ������ ������ ��ȭ ����Դϴ�.
// ���õ� �ε����� ���� ��ȭ ��尡 ����Ǿ��־�� �մϴ�.
// =====================================================================================

#include "PCH.h"
#include "TriggerDialogNode.h"

#include "Controller\ConsoleController.h"
#include "DialogConstant.h"

void TriggerDialogNode::Draw(Int32 x, Int32 y) const
{
	DialogNode::Draw(x, y);
	
	Int32 drawPosY = DIALOG_BOX_HEIGHT + 1;
	for (const auto& iter : m_vecTrigger)
	{
		const TupleTriggerDialogNode& tuple = *iter;
		PRINTF(x + 4, ++drawPosY, std::get<0>(tuple).c_str());
	}

	// Ʈ���Ű� ������ ���� �����͸� ������� �ؿ�!
	ConsoleController::I()->DrawSelector();
}

std::shared_ptr<DialogNode> TriggerDialogNode::FindNextNode() const
{
	const ConsoleSelector& consoleSelector = ConsoleController::I()->getCurrentConsoleSelector();
	Int32 selectedIdx = consoleSelector.getSelectorPos().Y - consoleSelector.getMinSelectorPos().Y;

	CHECK_RANGE(selectedIdx, 0, static_cast<Int32>(m_vecTrigger.size() - 1));
	std::shared_ptr<TupleTriggerDialogNode> spTupleTriggerNode = m_vecTrigger.at(selectedIdx);

	return std::get<1>(*spTupleTriggerNode);
}

void TriggerDialogNode::AddTrigger(const std::string& strTrigger, std::shared_ptr<DialogNode> spNextNode)
{
	std::shared_ptr<TupleTriggerDialogNode> spTriggerNode = std::make_shared<TupleTriggerDialogNode>();
	std::get<0>(*spTriggerNode) = strTrigger;
	std::get<1>(*spTriggerNode) = spNextNode;

	m_vecTrigger.push_back(spTriggerNode);
}
