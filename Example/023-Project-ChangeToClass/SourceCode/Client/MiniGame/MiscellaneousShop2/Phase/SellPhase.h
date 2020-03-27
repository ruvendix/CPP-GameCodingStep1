// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 판매 페이즈입니다.
// 판매 페이즈에서는 아이템을 판매할 수 있습니다.
// =====================================================================================

#ifndef SELL_PHASE_H__
#define SELL_PHASE_H__

#include "PhaseBase.h"

class SellPhase : public PhaseBase
{
	FRIEND_WITH_HELPER(SellPhaseHelper);
	INPUT_FPS_LIMITED(12);

public:
#pragma region 생성자 및 소멸자
	using PhaseBase::PhaseBase;
	virtual ~SellPhase() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;
};

#endif