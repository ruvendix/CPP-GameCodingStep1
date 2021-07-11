// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 타임 핸들러의 인터페이스입니다.
// 외부 데이터와 함수를 갖고 있으니 추상 클래스이기도 합니다.
// 시간 변환 등 시간 관련 내용을 다룹니다.
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

	// GraphEdge 생성 및 설정
	constexpr Int32 edgeCount = (nodeCount - 1);
	std::array<EdgeType*, edgeCount> positiveEdges; // 낮은 단위 -> 높은 단위
	std::array<EdgeType*, edgeCount> negativeEdges; // 높은 단위 -> 낮은 단위
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

		// 노드에 엣지를 연결
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
	// 테스트로 출력해보자
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

	// 시간 단위 변환은 미리 만들어놓은 그래프를 이용합니다.
	// 각 단위마다 변환될 때 사용되는 값이 다르므로 그래프가 적절합니다.
	// 미리 만들어놓은 그래프를 사용하므로 처리 속도는 빠른 편입니다.

	Int32 currentStep = ToUnderlyingType(src);
	Int32 diffStep = currentStep - ToUnderlyingType(dest);
	
	bool bPositive = true; // 낮은 단위에서 높은 단위로 변환할 때입니다.
	if (diffStep < 0)
	{
		diffStep *= -1;// 누적 횟수로 사용하기 위해 부호를 바꿉니다.
	}
	else // 높은 단위에서 낮은 단위로 변환할 때입니다.
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
		"일", "월", "화", "수", "목", "금", "토"
	};
	
	std::array<std::string, timeUnitCount> strTimeUnits;

	// 각 시간 단위 넣기
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

	// 각 시간 단위의 표시 순서 정하기
	TimeData::TimeOrders& timeOrders = Data()->GetTimeOrders();
	for (Uint32 i = 0; i < timeUnitCount; ++i)
	{
		EnumIdx::TimeUnit::Data orderIdx = timeOrders[i];

		const std::string& strTimeUnit = strTimeUnits[orderIdx];
		if (strTimeUnit.empty() == true) // 해당 시간 단위를 사용하지 않겠다는 의미
		{
			continue;
		}

		strLocalTime += strTimeUnit;
		strLocalTime += delimiter;
	}

	// delimiter 제거
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

	// 이전 시간 단위와 현재 시간 단위가 같다면 변경하는 의미가 없습니다.
	EnumIdx::TimeUnit::Data prevTimeUnit = timeOrders[orderIdx];
	if (prevTimeUnit == timeUnit)
	{
		return;
	}

	// 현재 넣을 인덱스와 값 교체
	timeOrders[orderIdx] = timeUnit;
	timeOrders[prevIdx] = prevTimeUnit;
}