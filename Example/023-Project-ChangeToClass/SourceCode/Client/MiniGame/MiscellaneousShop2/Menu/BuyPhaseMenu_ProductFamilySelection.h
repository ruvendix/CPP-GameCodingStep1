// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 구매 페이즈에서 사용되는 메뉴입니다.
// 선택된 제품군의 정보를 보여줍니다.
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

#pragma region 생성자 및 소멸자
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