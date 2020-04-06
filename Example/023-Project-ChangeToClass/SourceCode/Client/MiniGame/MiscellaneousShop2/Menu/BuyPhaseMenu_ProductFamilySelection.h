// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ������� ���Ǵ� �޴��Դϴ�.
// ���õ� ��ǰ���� ������ �����ݴϴ�.
// =====================================================================================

#ifndef BUY_PHASE_MENU_PRODUCT_FAMILY_SELECTION_H__
#define BUY_PHASE_MENU_PRODUCT_FAMILY_SELECTION_H__

#include "Element\Menu\Menu.h"
#include "..\Item\ItemDBType.h"

class BuyPhase;

class BuyPhaseMenu_ProductFamilySelection : public Menu
{
public:
	using Menu::Menu;

#pragma region ������ �� �Ҹ���
	BuyPhaseMenu_ProductFamilySelection() = default;
	virtual ~BuyPhaseMenu_ProductFamilySelection() = default;

	BuyPhaseMenu_ProductFamilySelection(const std::string_view& szNameTag, const COORD& pos,
		EItemDBType itemDBType, BuyPhase* pTargetPhase);
#pragma endregion

	virtual EErrorType OnExcute() override;

private:
	EItemDBType m_itemDBType = EItemDBType::NONE;
	BuyPhase* m_pTargetPhase = nullptr;
};

#endif