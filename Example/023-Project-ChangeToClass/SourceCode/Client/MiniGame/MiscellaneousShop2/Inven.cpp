// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 플레이어의 인벤토리입니다.
// 지금은 상점 아이템만 저장할 수 있습니다.
// =====================================================================================

#include "PCH.h"
#include "Inven.h"

#include "Common\CommonMacro.h"
#include "Controller\ConsoleController.h"
#include "PlayerContext.h"
#include "Item\ItemBase.h"

class PredInvenItemInfo
{
public:
	PredInvenItemInfo(const std::string& strItemNameTag)
		: m_strItemNameTag(strItemNameTag)
	{

	}

	~PredInvenItemInfo() = default;

	bool operator()(const InvenItemInfoPtr spInvenItemInfo)
	{
		CHECK_NULLPTR_RETURN(spInvenItemInfo, false);
		CHECK_NULLPTR(spInvenItemInfo->spItem);

		return (m_strItemNameTag == spInvenItemInfo->spItem->getNameTag());
	}

private:
	std::string m_strItemNameTag;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Inven::Inven()
{
	m_vecInvenItemInfo.resize(m_maxInvenSize);
}

void Inven::AddInvenItemInfo(ItemBasePtr spItem)
{
	InvenItemInfoPtr spInvenItemInfo = FindInvenItemInfo(spItem->getNameTag());
	if (spInvenItemInfo != nullptr)
	{
		++(spInvenItemInfo->cnt);
	}
	else
	{
		spInvenItemInfo = std::make_shared<InvenItemInfo>();
		spInvenItemInfo->cnt = 1; // 최초로 인벤토리에 넣었으니 1개!
		spInvenItemInfo->spItem = spItem->Clone();
		
		// 비어있는 인덱스 찾기
		for (Int32 i = 0; i < m_maxInvenSize; ++i)
		{
			if (m_vecInvenItemInfo.at(i) == nullptr)
			{
				m_currentIdx = i;
				break;
			}
		}

		CHECK_RANGE(m_currentIdx, 0, m_maxInvenSize);
		m_vecInvenItemInfo[m_currentIdx] = spInvenItemInfo;
		rx_math::Clamp(m_currentIdx, 0, m_maxInvenSize);
	}	
}

// 인벤토리에서 아이템을 삭제할 때는 순서를 유지시켜야 해요!
void Inven::DeleteInvenItemInfo(Int32 invenIdx)
{
	CHECK_RANGE(invenIdx, 0, m_maxInvenSize - 1);

	auto& iter = m_vecInvenItemInfo.at(invenIdx);
	iter = nullptr;
}

void Inven::Draw(Int32 x, Int32 y) const
{
	if (m_vecInvenItemInfo.empty() == true)
	{
		PUT_STRING(0, 0, "인벤토리에 아이템이 없어요!");
		return;
	}

	Int32 drawPosY = y - 1;
	PUT_STRING(x, ++drawPosY, "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━┓");
	PUT_STRING(x, ++drawPosY, "┃    이름                            ┃ 소지┃");
	PUT_STRING(x, ++drawPosY, "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━┫");

	for (const auto& iter : m_vecInvenItemInfo)
	{
		if ( (iter == nullptr) ||
			 (iter->cnt <= 0) )
		{
			PUT_STRING(x, ++drawPosY, "┃    %-32s┃ %4d┃", "No Item", 0);
			continue;
		}

		PUT_STRING(x, ++drawPosY, "┃    %-32s┃ %4d┃", iter->spItem->getNameTag().c_str(), iter->cnt);
	}

	PUT_STRING(x, ++drawPosY, "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━┫");
	PUT_STRING(x, ++drawPosY, "┃         %-12d                     ┃", PlayerCtx::I()->getGameMoney());
	
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::AQUA);
	PUT_STRING(x + 2, drawPosY, "소지금:");
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::WHITE);

	PUT_STRING(x, ++drawPosY, "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
}

void Inven::DrawForSell(Int32 x, Int32 y) const
{
	if (m_vecInvenItemInfo.empty() == true)
	{
		PUT_STRING(0, 0, "인벤토리에 아이템이 없어요!");
		return;
	}

	Int32 drawPosY = y - 1;
	PUT_STRING(x, ++drawPosY, "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━┳━━━━━┓");
	PUT_STRING(x, ++drawPosY, "┃    이름                            ┃     가격┃ 소지┃");
	PUT_STRING(x, ++drawPosY, "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━╋━━━━━┫");

	for (const auto& iter : m_vecInvenItemInfo)
	{
		if ( (iter == nullptr) ||
			 (iter->cnt <= 0) )
		{
			PUT_STRING(x, ++drawPosY, "┃    %-32s┃ %8d┃ %4d┃", "No Item", 0, 0);
			continue;
		}

		ItemBasePtr spItem = iter->spItem;
		Int32 itemPrice = static_cast<Int32>(spItem->getPrice() * 0.8f);
		PUT_STRING(x, ++drawPosY, "┃    %-32s┃ %8d┃ %4d┃", spItem->getNameTag().c_str(), itemPrice, iter->cnt);
	}

	PUT_STRING(x, ++drawPosY, "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━┻━━━━━┫");
	PUT_STRING(x, ++drawPosY, "┃         %-12d                               ┃", PlayerCtx::I()->getGameMoney());

	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::AQUA);
	PUT_STRING(x + 2, drawPosY, "소지금:");
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::WHITE);

	PUT_STRING(x, ++drawPosY, "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
}

void Inven::Arrange()
{
	m_currentIdx = 0;

	std::vector<InvenItemInfoPtr> vecNew(m_maxInvenSize);
	for (auto& iter : m_vecInvenItemInfo)
	{
		CHECK_NULLPTR_CONTINUE(iter);
		vecNew[m_currentIdx] = iter;
		++m_currentIdx;
	}

	std::swap(m_vecInvenItemInfo, vecNew);
}

bool Inven::IsFull() const
{
	for (const auto& iter : m_vecInvenItemInfo)
	{
		if (iter == nullptr)
		{
			return false;
		}
	}

	return true;
}

InvenItemInfoPtr Inven::FindInvenItemInfo(const std::string& strItemNameTag) const
{
	auto iter = std::find_if(m_vecInvenItemInfo.cbegin(), m_vecInvenItemInfo.cend(), PredInvenItemInfo(strItemNameTag));
	if (iter != m_vecInvenItemInfo.cend())
	{
		return (*iter);
	}

	return nullptr;
}

InvenItemInfoPtr Inven::FindInvenItemInfo(Int32 invenIdx) const
{
	return m_vecInvenItemInfo.at(invenIdx);
}
