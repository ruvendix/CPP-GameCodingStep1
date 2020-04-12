// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �б� ������ ������ ��ȭ ����Դϴ�.
// ���õ� �ε����� ���� ��ȭ ��尡 ����Ǿ��־�� �մϴ�.
// =====================================================================================

#ifndef TRIGGER_DIALOG_NODE_H__
#define TRIGGER_DIALOG_NODE_H__

#include "DialogNode.h"

class TriggerDialogNode final : public DialogNode
{
	DECLARE_RTTI(TriggerDialogNode, DialogNode);

public:
	using TupleTriggerDialogNode = std::tuple<std::string, std::shared_ptr<DialogNode>>;

#pragma region ������ �� �Ҹ���
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