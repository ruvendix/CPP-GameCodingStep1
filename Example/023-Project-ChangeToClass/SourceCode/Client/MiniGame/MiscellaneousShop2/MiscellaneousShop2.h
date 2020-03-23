// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 다양한 아이템을 구매 및 판매하는 잡화상점2입니다.
// =====================================================================================

#ifndef MISCELLANEOUS_SHOP2_H__
#define MISCELLANEOUS_SHOP2_H__

#include "Element\GameElement.h"

class PhaseBase;

class MiscellanouseShop2 final : public GameElem
{
	FRIEND_WITH_HELPER(MiscellaneousShop2Helper);

public:
#pragma region 생성자 및 소멸자
	using GameElem::GameElem;
	virtual ~MiscellanouseShop2() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;

private:
	PhaseBase* m_pCurrentPhase = nullptr;
};

#endif