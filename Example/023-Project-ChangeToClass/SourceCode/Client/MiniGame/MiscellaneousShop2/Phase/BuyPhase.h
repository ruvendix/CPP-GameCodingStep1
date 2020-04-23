// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 구매 페이즈입니다.
// 구매 페이즈에서는 상점 아이템을 구매할 수 있습니다.
// =====================================================================================

#ifndef BUY_PHASE_H__
#define BUY_PHASE_H__

#include "Element\Phase.h"
#include "Element\Menu\MenuTable_Matrix.h"
#include "..\Item\ItemDBType.h"

class ItemBase;
using ItemBasePtr = std::shared_ptr<ItemBase>;

class BuyPhase final : public Phase
{
	DECLARE_RTTI(BuyPhase, Phase);
	FRIEND_WITH_HELPER(BuyPhaseHelper);
	INPUT_FPS_LIMITED(8);

public:
#pragma region 생성자 및 소멸자
	using Phase::Phase;
	virtual ~BuyPhase() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnRender() override;

	void ResetDisplayItem(TSize size)
	{
		m_vecDisplayItem.clear();
		m_vecDisplayItem.reserve(size);
	}

	void SelectedProductFamily(bool bResult)
	{
		m_bSelectedProductFamily = bResult;
	}

	void setCurrentItemDBType(EItemDBType type)
	{
		m_currentItemDBType = type;
	}

	std::vector<ItemBasePtr>& getVecDisplayItem()
	{
		return m_vecDisplayItem;
	}

private:
	EItemDBType m_currentItemDBType = EItemDBType::POTION;
	std::vector<ItemBasePtr> m_vecDisplayItem;
	bool m_bSelectedProductFamily = false;
	std::shared_ptr<MenuTable_Mat> m_spMenuTable;
};

#endif