// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �׷��������� ���Ǵ� �����Դϴ�.
// �����͸� ���� ������ ���� ���� �� ��带 �˰� �ֽ��ϴ�.
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