// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �÷��̾��� �κ��丮�Դϴ�.
// ������ ���� �����۸� ������ �� �ֽ��ϴ�.
// =====================================================================================

#include "PCH.h"
#include "Inven.h"

#include "Controller\ConsoleController.h"
#include "PlayerContext.h"
#include "Item\ItemBase.h"

class PredInvenItemInfo
{
public:
	PredInvenItemInfo(const std::string& strItemNameTag)
		: m_strItemNameTag(strItemNameTag) { }

	~PredInvenItemInfo() = default;

	bool operator()(const InvenItemInfo* pInvenItemInfo)
	{
		CHECK_NULLPTR(pInvenItemInfo);
		CHECK_NULLPTR(pInvenItemInfo->pItem);

		return (m_strItemNameTag == pInvenItemInfo->pItem->getNameTag());
	}

private:
	std::string m_strItemNameTag;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Inven::~Inven()
{
	for (auto& iter : m_vecInvenItemInfo)
	{
		SAFE_DELETE(iter->pItem);
		SAFE_DELETE(iter);
	}
}

InvenItemInfo* Inven::FindInvenItemInfo(const std::string& strItemNameTag) const
{
	auto iter = std::find_if(m_vecInvenItemInfo.cbegin(), m_vecInvenItemInfo.cend(), PredInvenItemInfo(strItemNameTag));
	if (iter != m_vecInvenItemInfo.cend())
	{
		return (*iter);
	}

	return nullptr;
}

void Inven::AddInvenItemInfo(const ItemBase* pItem)
{
	InvenItemInfo* pInvenItemInfo = FindInvenItemInfo(pItem->getNameTag());
	if (pInvenItemInfo != nullptr)
	{
		++(pInvenItemInfo->cnt);
	}
	else
	{
		pInvenItemInfo = trace_new InvenItemInfo;
		pInvenItemInfo->cnt = 1; // ���ʷ� �κ��丮�� �־����� 1��!
		pInvenItemInfo->pItem = pItem->Clone();
		m_vecInvenItemInfo.push_back(pInvenItemInfo);
	}	
}

// �κ��丮���� �������� ������ ���� ������ �������Ѿ� �ؿ�!
void Inven::DeleteInvenItemInfo(const std::string& strItemNameTag)
{
	InvenItemInfo* pInvenItemInfo = FindInvenItemInfo(strItemNameTag);
	SAFE_DELETE(pInvenItemInfo->pItem);
	SAFE_DELETE(pInvenItemInfo);
}

void Inven::DrawInven(Int32 x, Int32 y) const
{
	if (m_vecInvenItemInfo.empty() == true)
	{
		PRINTF(0, 0, "�κ��丮�� �������� �����!");
		return;
	}

	Int32 drawPosY = y - 1;
	PRINTF(x, ++drawPosY, "����������������������������������������������������������������������������������������");
	PRINTF(x, ++drawPosY, "��    �̸�                            �� ������");
	PRINTF(x, ++drawPosY, "����������������������������������������������������������������������������������������");

	for (const auto& iter : m_vecInvenItemInfo)
	{
		if (iter == nullptr)
		{
			continue;
		}

		ItemBase* pItem = iter->pItem;
		if (pItem == nullptr)
		{
			continue;
		}

		PRINTF(x, ++drawPosY, "��    %-32s�� %4d��", pItem->getNameTag().c_str(), iter->cnt);
	}

	PRINTF(x, ++drawPosY, "����������������������������������������������������������������������������������������");
	PRINTF(x, ++drawPosY, "��         %-12d                     ��", PlayerCtx::I()->getGameMoney());
	
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::AQUA);
	PRINTF(x + 2, drawPosY, "������:");
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::WHITE);

	PRINTF(x, ++drawPosY, "����������������������������������������������������������������������������������������");
}

void Inven::DrawInvenForSell(Int32 x, Int32 y) const
{
	if (m_vecInvenItemInfo.empty() == true)
	{
		PRINTF(0, 0, "�κ��丮�� �������� �����!");
		return;
	}

	Int32 drawPosY = y - 1;
	PRINTF(x, ++drawPosY, "������������������������������������������������������������������������������������������������������������");
	PRINTF(x, ++drawPosY, "��    �̸�                            ��     ���ݦ� ������");
	PRINTF(x, ++drawPosY, "������������������������������������������������������������������������������������������������������������");

	for (Int32 i = 0; i < m_maxInvenSize; ++i)
	{
		if (i >= static_cast<Int32>(m_vecInvenItemInfo.size()))
		{
			PRINTF(x, ++drawPosY, "��    %-32s�� %8d�� %4d��", "No Item", 0, 0);
			continue;
		}

		InvenItemInfo* pInvenItemInfo = m_vecInvenItemInfo.at(i);
		CHECK_NULLPTR_CONTINUE(pInvenItemInfo);

		ItemBase* pItem = pInvenItemInfo->pItem;
		CHECK_NULLPTR_CONTINUE(pItem);

		Int32 itemPrice = static_cast<Int32>(pItem->getPrice() * 0.8f);
		PRINTF(x, ++drawPosY, "��    %-32s�� %8d�� %4d��", pItem->getNameTag().c_str(), itemPrice, pInvenItemInfo->cnt);
	}

	PRINTF(x, ++drawPosY, "������������������������������������������������������������������������������������������������������������");
	PRINTF(x, ++drawPosY, "��         %-12d                               ��", PlayerCtx::I()->getGameMoney());

	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::AQUA);
	PRINTF(x + 2, drawPosY, "������:");
	ConsoleController::I()->ChangeConsoleOutputColor(EConsoleOutputType::TEXT, EConsoleOutputColorType::WHITE);

	PRINTF(x, ++drawPosY, "������������������������������������������������������������������������������������������������������������");
}

bool Inven::IsFull() const
{
	if (m_maxInvenSize <= static_cast<Int32>(m_vecInvenItemInfo.size()))
	{
		return true;
	}

	return false;
}
