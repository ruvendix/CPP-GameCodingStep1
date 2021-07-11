// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 노드와 엣지로 이루어져있는 그래프입니다.
// 단방향 엣지를 이용하고 데이터는 엣지에만 있습니다.
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

	// 이렇게 따로 삭제해야 상호참조 문제를 해결할 수 있습니다.
	// std::weak_ptr을 사용해도 괜찮지만 귀찮아서 이렇게...
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