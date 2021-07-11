// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 그래프에서만 사용되는 노드입니다.
// =====================================================================================
#pragma once

#include "Common/CommonType.h"

template <typename TData, typename TEdge>
class GraphNode
{
public:
	using DataType = TData;
	using EdgeType = TEdge;

	GraphNode(Uint32 idx)
	{
		m_idx = idx;
	}

	~GraphNode() = default;

	Uint32 GetIdx() const { return m_idx; }

	EdgeType* GetPrevEdge() { return m_pPrevEdge; }
	const EdgeType* GetPrevEdge() const { return m_pPrevEdge; }
	void SetPrevEdge(EdgeType* pPrevEdge) { m_pPrevEdge = pPrevEdge; }

	EdgeType* GetNextEdge() { return m_pNextEdge; }
	const EdgeType* GetNextEdge() const { return m_pNextEdge; }
	void SetNextEdge(EdgeType* pNextEdge) { m_pNextEdge = pNextEdge; }

private:
	Uint32 m_idx = 0;
	EdgeType* m_pPrevEdge = nullptr;
	EdgeType* m_pNextEdge = nullptr;
};