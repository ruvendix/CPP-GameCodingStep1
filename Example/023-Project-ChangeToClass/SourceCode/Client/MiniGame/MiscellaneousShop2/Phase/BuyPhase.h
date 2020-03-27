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

#include "PhaseBase.h"
#include "..\Item\ItemDBEnum.h"

class ItemBase;

class BuyPhase : public PhaseBase
{
	FRIEND_WITH_HELPER(BuyPhaseHelper);
	INPUT_FPS_LIMITED(12);

public:
#pragma region 생성자 및 소멸자
	using PhaseBase::PhaseBase;
	virtual ~BuyPhase() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;

private:
	EItemDBType m_itemDBType = EItemDBType::POTION;
	std::vector<ItemBase*> m_vecDisplayItem;
	bool m_bSelectedProductFamily = false;
};

#endif