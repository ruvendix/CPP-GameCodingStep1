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

#include "PhaseBase.h"

class ArrangePhase : public PhaseBase
{
public:
#pragma region 생성자 및 소멸자
	using PhaseBase::PhaseBase;
	virtual ~ArrangePhase() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnRender() override;
};

#endif