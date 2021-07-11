// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 그래프에서만 사용되는 엣지입니다.
// 데이터를 갖고 있으며 시작 노드와 끝 노드를 알고 있습니다.
// =====================================================================================
#pragma once

#include "Common/CommonType.h"

template <typename TData>
class GraphEdge
{
public:
	using DataType = TData;
	using NodeType = GraphNode<TData, GraphEdge<TData>>;

	GraphEdge(NodeType* pStart, NodeType* pEnd, const DataType& data)
	{
		m_pStart = pStart;
		m_pEnd = pEnd;
		m_data = data;
	}

	~GraphEdge() = default;

	NodeType* GetStart() const { return m_pStart; }
	NodeType* GetEnd() const { return m_pEnd; }

	DataType& GetData() { return m_data; }
	const DataType& GetData() const { return m_data; }

private:
	NodeType* m_pStart = nullptr;
	NodeType* m_pEnd = nullptr;
	DataType m_data;
};