// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��ȭ ����Դϴ�.
// ���� ��ȭ ��� ������ ������ �� �˴ϴ�!
// =====================================================================================

#ifndef DIALOG_NODE_H__
#define DIALOG_NODE_H__

#include "Common\CommonType.h"
#include "Common\CommonNecessary.h"

struct DialogInfo
{
	std::string strSpeaker;
	std::string strScript;
};

class DialogNode
{
public:
#pragma region ������ �� �Ҹ���
	DialogNode() = default;
	virtual ~DialogNode() = default;

	DialogNode(const std::string_view& szSpeaker, const std::string_view& szScript);
#pragma endregion

	virtual void Draw(Int32 x, Int32 y) const;
	virtual std::shared_ptr<DialogNode> FindNextNode() const;

	void setNextNode(const std::shared_ptr<DialogNode>& spNextNode)
	{
		m_spNextNode = spNextNode;
	}

private:
	std::unique_ptr<DialogInfo> m_spInfo; // �⺻ ��� ����
	std::shared_ptr<DialogNode> m_spNextNode;
};

#endif