// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 정리 페이즈입니다.
// 정리 페이즈에서는 인벤토리를 정리할 수 있습니다.
// =====================================================================================

#ifndef ARRANGE_PHASE_H__
#define ARRANGE_PHASE_H__

#include "Element\Phase.h"

class ArrangePhase : public Phase
{
public:
#pragma region 생성자 및 소멸자
	using Phase::Phase;
	virtual ~ArrangePhase() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnRender() override;
};

#endif