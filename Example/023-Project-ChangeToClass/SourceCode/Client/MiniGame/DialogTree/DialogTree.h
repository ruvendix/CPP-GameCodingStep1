// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��ȭ Ʈ���Դϴ�.
// ��ȭ ��带 �����ϰ� �����ϴ� ���� ó���� �մϴ�.
// =====================================================================================

#ifndef DIALOG_TREE_H__
#define DIALOG_TREE_H__

#include "Common\CommonType.h"
#include "Common\CommonNecessary.h"
#include "DialogNode.h"

class DialogTree final
{
public:
#pragma region ������ �� �Ҹ���
	DialogTree();
	~DialogTree() = default;
#pragma endregion

	template<typename TDialogNode>
	std::shared_ptr<TDialogNode> CreateNode(const std::string_view& szSpeaker, const std::string_view& szScript)
	{
		return std::make_shared<TDialogNode>(szSpeaker, szScript);
	}

	template<typename TDialogNode>
	std::shared_ptr<TDialogNode> LinkNewNextNode(std::shared_ptr<DialogNode> spNode,
		const std::string_view& szSpeaker, const std::string_view& szScript)
	{
		std::shared_ptr<TDialogNode> spNextNode = CreateNode<TDialogNode>(szSpeaker, szScript);
		spNode->setNextNode(spNextNode);

		return spNextNode;
	}

	const std::shared_ptr<DialogNode> getRootNode() const
	{
		return m_spRootNode;
	}

	void setRootNode(const std::shared_ptr<DialogNode>& spNode)
	{
		m_spRootNode = spNode;
	}

private:
	std::shared_ptr<DialogNode> m_spRootNode;
};

#endif