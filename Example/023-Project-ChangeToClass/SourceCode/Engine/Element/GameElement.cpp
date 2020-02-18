// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 모든 게임 요소의 기반입니다.
// =====================================================================================

#include "PCH.h"
#include "GameElement.h"

EErrorType GameElement::OnInitialize()
{
	DEBUG_LOG("GameElement에서 이게 보이면 OnInitialize()를 재정의해주세요!");
	return EErrorType::NONE;
}

EErrorType GameElement::OnUpdate()
{
	DEBUG_LOG("GameElement에서 이게 보이면 OnUpdate()를 재정의해주세요!");
	return EErrorType::NONE;
}

EErrorType GameElement::OnRender()
{
	DEBUG_LOG("GameElement에서 이게 보이면 OnRender()를 재정의해주세요!");
	return EErrorType::NONE;
}

EErrorType GameElement::OnFinalize()
{
	DEBUG_LOG("GameElement에서 이게 보이면 OnFinalize()를 재정의해주세요!");
	return EErrorType::NONE;
}
