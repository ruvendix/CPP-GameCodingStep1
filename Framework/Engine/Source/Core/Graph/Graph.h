// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ������ �̷�����ִ� �׷����Դϴ�.
// �ܹ��� ������ �̿��ϰ� �����ʹ� �������� �ֽ��ϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonType.h"

template <typename TData>
class Graph
{
public:
	using DataType = TData;
	using EdgeType = GraphEdge<TData>;
	using NodeType = GraphNode<TData, EdgeType>;

	Graph() = default;

	// �̷��� ���� �����ؾ� ��ȣ���� ������ �ذ��� �� �ֽ��ϴ�.
	// std::weak_ptr�� ����ص� �������� �����Ƽ� �̷���...
	~Graph()
	{
		for (auto& iter : m_vecEdge)
		{
			SAFE_DELETE(iter);
		}

		for (auto& iter : m_vecNode)
		{
			SAFE_DELETE(iter);
		}
	}

	void AddNode(NodeType* pNode)
	{
		m_vecNode.push_back(pNode);
	}

	void AddEdge(EdgeType* pEdge)
	{
		m_vecEdge.push_back(pEdge);
	}

	NodeType* GetNode(Uint32 idx) { return m_vecNode[idx]; }
	const NodeType* GetNode(Uint32 idx) const { return m_vecNode[idx]; }

private:
	std::vector<NodeType*> m_vecNode;
	std::vector<EdgeType*> m_vecEdge;
};