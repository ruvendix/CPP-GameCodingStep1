// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 분기 선택이 가능한 대화 노드입니다.
// 선택된 인덱스와 다음 대화 노드가 연결되어있어야 합니다.
// =====================================================================================

#ifndef TRIGGER_DIALOG_NODE_H__
#define TRIGGER_DIALOG_NODE_H__

#include "DialogNode.h"

class TriggerDialogNode final : public DialogNode
{
	DECLARE_RTTI(TriggerDialogNode, DialogNode);

public:
	using TupleTriggerDialogNode = std::tuple<std::string, std::shared_ptr<DialogNode>>;

#pragma region 생성자 및 소멸자
	using DialogNode::DialogNode;
	virtual ~TriggerDialogNode() = default;
#pragma endregion

	virtual void Draw(Int32 x, Int32 y) const override;
	virtual std::shared_ptr<DialogNode> FindNextNode() const override;

	void AddTrigger(const std::string& strTrigger, std::shared_ptr<DialogNode> spNextNode);

	Int32 getTriggerCnt() const
	{
		return static_cast<Int32>(m_vecTrigger.size());
	}

private:
	std::vector<std::shared_ptr<TupleTriggerDialogNode>> m_vecTrigger;
};

#endif