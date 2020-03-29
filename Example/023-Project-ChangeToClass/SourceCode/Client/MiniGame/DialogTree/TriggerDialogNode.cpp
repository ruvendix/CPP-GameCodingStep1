// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 분기 선택이 가능한 대화 노드입니다.
// 선택된 인덱스와 다음 대화 노드가 연결되어있어야 합니다.
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

	// 트리거가 존재할 때는 셀렉터를 보여줘야 해요!
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
