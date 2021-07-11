// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Ÿ�� �ڵ鷯�� �������̽��Դϴ�.
// �ܺ� �����Ϳ� �Լ��� ���� ������ �߻� Ŭ�����̱⵵ �մϴ�.
// �ð� ��ȯ �� �ð� ���� ������ �ٷ�ϴ�.
// =====================================================================================
#include "EnginePCH.h"
#include "TimeHandler.h"

#include "Base/TimeData.h"
#include "Core/Graph/GraphInclusion.h"

class TimeHandlerInside final
{
public:
	TimeHandlerInside();
	~TimeHandlerInside() = default;

	void Initialize();
	Float ConvertTime(Float time, EConvertionTimeUnit src, EConvertionTimeUnit dest) const;

private:
	using GraphType = Graph<Float>;
	using EdgeType = GraphEdge<Float>;
	using NodeType = GraphNode<Float, EdgeType>;

	std::unique_ptr<GraphType> m_spGraph = nullptr;
};

TimeHandlerInside::TimeHandlerInside()
{
	m_spGraph = std::make_unique<GraphType>();
}

void TimeHandlerInside::Initialize()
{
	constexpr Int32 nodeCount = ToUnderlyingType(EConvertionTimeUnit::COUNT);
	std::array<NodeType*, nodeCount> nodes;
	for (Int32 i = 0; i < nodeCount; ++i)
	{
		nodes[i] = new NodeType(i);
	}

	// GraphEdge ���� �� ����
	constexpr Int32 edgeCount = (nodeCount - 1);
	std::array<EdgeType*, edgeCount> positiveEdges; // ���� ���� -> ���� ����
	std::array<EdgeType*, edgeCount> negativeEdges; // ���� ���� -> ���� ����
	{
		positiveEdges[0] = new GraphEdge(nodes[0], nodes[1], 1.0f / 1000.0f); // 0 -> 1
		positiveEdges[1] = new GraphEdge(nodes[1], nodes[2], 1.0f / 60.0f); // 1 -> 2
		positiveEdges[2] = new GraphEdge(nodes[2], nodes[3], 1.0f / 60.0f); // 2 -> 3
		positiveEdges[3] = new GraphEdge(nodes[3], nodes[4], 1.0f / 24.0f); // 3 -> 4
		positiveEdges[4] = new GraphEdge(nodes[4], nodes[5], 1.0f / 365.0f); // 4 -> 5

		negativeEdges[0] = new GraphEdge(nodes[0], nodes[1], 1000.0f); // 1 -> 0
		negativeEdges[1] = new GraphEdge(nodes[1], nodes[2], 60.0f); // 2 -> 1
		negativeEdges[2] = new GraphEdge(nodes[2], nodes[3], 60.0f); // 3 -> 2
		negativeEdges[3] = new GraphEdge(nodes[3], nodes[4], 24.0f); // 4 -> 3
		negativeEdges[4] = new GraphEdge(nodes[4], nodes[5], 365.0f); // 5 -> 4

		// ��忡 ������ ����
		{
			nodes[0]->SetNextEdge(positiveEdges[0]); // 0 -> 1

			nodes[1]->SetPrevEdge(negativeEdges[0]); // 1 -> 0
			nodes[1]->SetNextEdge(positiveEdges[1]); // 1 -> 2

			nodes[2]->SetPrevEdge(negativeEdges[1]); // 2 -> 1
			nodes[2]->SetNextEdge(positiveEdges[2]); // 2 -> 3

			nodes[3]->SetPrevEdge(negativeEdges[2]); // 3 -> 2
			nodes[3]->SetNextEdge(positiveEdges[3]); // 3 -> 4

			nodes[4]->SetPrevEdge(negativeEdges[3]); // 4 -> 3
			nodes[4]->SetNextEdge(positiveEdges[4]); // 4 -> 5

			nodes[5]->SetPrevEdge(negativeEdges[4]); // 5 -> 4
		}
	}

	for (Int32 i = 0; i < nodeCount; ++i)
	{
		m_spGraph->AddNode(nodes[i]);
	}

	for (Int32 i = 0; i < edgeCount; ++i)
	{
		m_spGraph->AddEdge(positiveEdges[i]);
		m_spGraph->AddEdge(negativeEdges[i]);
	}

#if 0
	// �׽�Ʈ�� ����غ���
	for (Int32 i = 0; i < nodeCount; ++i)
	{
		const NodeType* pNode = m_spGraph->GetNode(i);
		const EdgeType* pPrevEdge = pNode->GetPrevEdge();
		const EdgeType* pNextEdge = pNode->GetNextEdge();

		RX_TRACE("-----------------------------");
		if (pPrevEdge != nullptr)
		{
			RX_TRACE("%d -> %d: %f", i, i - 1, pPrevEdge->GetData());
		}

		if (pNextEdge != nullptr)
		{
			RX_TRACE("%d -> %d: %f", i, i + 1, pNextEdge->GetData());
		}
		RX_TRACE("-----------------------------");
	}
#endif
}

Float TimeHandlerInside::ConvertTime(Float time, EConvertionTimeUnit src, EConvertionTimeUnit dest) const
{
	if (src == dest)
	{
		return time;
	}

	// �ð� ���� ��ȯ�� �̸� �������� �׷����� �̿��մϴ�.
	// �� �������� ��ȯ�� �� ���Ǵ� ���� �ٸ��Ƿ� �׷����� �����մϴ�.
	// �̸� �������� �׷����� ����ϹǷ� ó�� �ӵ��� ���� ���Դϴ�.

	Int32 currentStep = ToUnderlyingType(src);
	Int32 diffStep = currentStep - ToUnderlyingType(dest);
	
	bool bPositive = true; // ���� �������� ���� ������ ��ȯ�� ���Դϴ�.
	if (diffStep < 0)
	{
		diffStep *= -1;// ���� Ƚ���� ����ϱ� ���� ��ȣ�� �ٲߴϴ�.
	}
	else // ���� �������� ���� ������ ��ȯ�� ���Դϴ�.
	{		
		bPositive = false;
	}

	Float ret = 1.0f;
	for (Int32 i = 0; i < diffStep; ++i)
	{
		const NodeType* pNode = m_spGraph->GetNode(currentStep);
		RX_ASSERT(pNode != nullptr);

		const EdgeType* pEdge = nullptr;
		if (bPositive == true)
		{
			++currentStep;
			pEdge = pNode->GetNextEdge();
		}
		else
		{
			--currentStep;
			pEdge = pNode->GetPrevEdge();
		}

		RX_ASSERT(pEdge != nullptr);
		ret *= time * pEdge->GetData();
	}

	return ret;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
TimeHandler::TimeHandler()
{
	m_spInside = std::make_unique<TimeHandlerInside>();
}

void TimeHandler::SetUp()
{
	m_spInside->Initialize();

	TimeData::TimeOrders& timeOrders = Data()->GetTimeOrders();
	for (Uint32 i = 0; i < EnumIdx::TimeUnit::COUNT; ++i)
	{
		EnumIdx::TimeUnit::Data timeUnit = static_cast<EnumIdx::TimeUnit::Data>(i);
		ActivateTimeUnit(timeUnit);

		timeOrders[i] = timeUnit;
	}
}

void TimeHandler::CleanUp()
{

}

Float TimeHandler::ConvertTime(Float time, EConvertionTimeUnit src, EConvertionTimeUnit dest) const
{
	return m_spInside->ConvertTime(time, src, dest);
}

void TimeHandler::MakeLocalTimeString(OUT std::string& strLocalTime, Char delimiter)
{
	SYSTEMTIME systemTime;
	::GetLocalTime(&systemTime);

	constexpr Uint32 timeUnitCount = EnumIdx::TimeUnit::COUNT;
	std::array<WORD, timeUnitCount> localTime =
	{
		systemTime.wYear,
		systemTime.wMonth,
		systemTime.wDayOfWeek,
		systemTime.wDay,
		systemTime.wHour,
		systemTime.wMinute,
		systemTime.wSecond,
		systemTime.wMilliseconds
	};

	std::array<std::string, 7> strDayOfWeek =
	{
		"��", "��", "ȭ", "��", "��", "��", "��"
	};
	
	std::array<std::string, timeUnitCount> strTimeUnits;

	// �� �ð� ���� �ֱ�
	for (Uint32 i = 0; i < timeUnitCount; ++i)
	{
		EnumIdx::TimeUnit::Data timeUnit = static_cast<EnumIdx::TimeUnit::Data>(i);
		if (CheckTimeUnit(timeUnit) == false)
		{
			continue;
		}

		if (timeUnit == EnumIdx::TimeUnit::DAY_OF_WEEK)
		{
			strTimeUnits[timeUnit] = strDayOfWeek[localTime[timeUnit]];
		}
		else
		{
			strTimeUnits[i] = std::to_string(localTime[i]);
		}
	}

	strLocalTime.clear();

	// �� �ð� ������ ǥ�� ���� ���ϱ�
	TimeData::TimeOrders& timeOrders = Data()->GetTimeOrders();
	for (Uint32 i = 0; i < timeUnitCount; ++i)
	{
		EnumIdx::TimeUnit::Data orderIdx = timeOrders[i];

		const std::string& strTimeUnit = strTimeUnits[orderIdx];
		if (strTimeUnit.empty() == true) // �ش� �ð� ������ ������� �ʰڴٴ� �ǹ�
		{
			continue;
		}

		strLocalTime += strTimeUnit;
		strLocalTime += delimiter;
	}

	// delimiter ����
	strLocalTime.pop_back();
}

void TimeHandler::ActivateTimeUnit(EnumIdx::TimeUnit::Data timeUnit)
{
	Data()->GetTimeUnits().set(timeUnit, true);
}

void TimeHandler::DeactivateTimeUnit(EnumIdx::TimeUnit::Data timeUnit)
{
	Data()->GetTimeUnits().set(timeUnit, false);
}

bool TimeHandler::CheckTimeUnit(EnumIdx::TimeUnit::Data timeUnit) const
{
	return Data()->GetTimeUnits().test(ToUnderlyingType(timeUnit));
}

void TimeHandler::ChangeTimeOrder(EnumIdx::TimeUnit::Data timeUnit, Uint32 orderIdx)
{
	TimeData::TimeOrders& timeOrders = Data()->GetTimeOrders();

	Int32 prevIdx = -1;
	for (Uint32 i = 0; i < EnumIdx::TimeUnit::COUNT; ++i)
	{
		if (timeOrders[i] == timeUnit)
		{
			prevIdx = i;
			break;
		}
	}

	// ���� �ð� ������ ���� �ð� ������ ���ٸ� �����ϴ� �ǹ̰� �����ϴ�.
	EnumIdx::TimeUnit::Data prevTimeUnit = timeOrders[orderIdx];
	if (prevTimeUnit == timeUnit)
	{
		return;
	}

	// ���� ���� �ε����� �� ��ü
	timeOrders[orderIdx] = timeUnit;
	timeOrders[prevIdx] = prevTimeUnit;
}