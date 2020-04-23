// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �������Դϴ�.
// ���� ��������� ���� �������� ������ �� �ֽ��ϴ�.
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
#pragma region ������ �� �Ҹ���
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