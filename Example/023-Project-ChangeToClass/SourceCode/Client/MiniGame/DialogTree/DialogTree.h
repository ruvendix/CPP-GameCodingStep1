// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 대화 트리입니다.
// 대화 노드를 생성하고 연결하는 등의 처리를 합니다.
// =====================================================================================

#ifndef DIALOG_TREE_H__
#define DIALOG_TREE_H__

#include "Common\CommonType.h"
#include "Common\CommonNecessary.h"
#include "DialogNode.h"

class DialogTree final
{
public:
#pragma region 생성자 및 소멸자
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