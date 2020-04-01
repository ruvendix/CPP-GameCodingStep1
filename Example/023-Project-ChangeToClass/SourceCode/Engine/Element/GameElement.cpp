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

EErrorType GameElem::OnInitialize()
{
	//DEBUG_LOG("GameElem에서 이게 보이면 OnInitialize()를 재정의해주세요!");
	return EErrorType::NONE;
}

EErrorType GameElem::OnPostInitialize()
{
	//DEBUG_LOG("GameElem에서 이게 보이면 OnPostInitialize()를 재정의해주세요!");
	return EErrorType::NONE;
}

EErrorType GameElem::OnInput()
{
	if (m_bFirstInput == true)
	{
		m_bFirstInput = false;
		return EErrorType::FIRST_INPUT; // 에러는 아니지만 반환을 위해
	}

	//DEBUG_LOG("GameElem에서 이게 보이면 OnInput()를 재정의해주세요!");
	return EErrorType::NONE;
}

EErrorType GameElem::OnUpdate()
{
	//DEBUG_LOG("GameElem에서 이게 보이면 OnUpdate()를 재정의해주세요!");
	return EErrorType::NONE;
}

EErrorType GameElem::OnRender()
{
	//DEBUG_LOG("GameElem에서 이게 보이면 OnRender()를 재정의해주세요!");
	return EErrorType::NONE;
}

EErrorType GameElem::OnFinalize()
{
	//DEBUG_LOG("GameElem에서 이게 보이면 OnFinalize()를 재정의해주세요!");
	return EErrorType::NONE;
}

EErrorType GameElem::OnSaveFile(const std::string_view& szFileName)
{
	//DEBUG_LOG("GameElem에서 이게 보이면 OnSaveFile()를 재정의해주세요!");
	return EErrorType::NONE;
}

EErrorType GameElem::OnLoadFile(const std::string_view& szFileName)
{
	//DEBUG_LOG("GameElem에서 이게 보이면 OnLoadFile()를 재정의해주세요!");
	return EErrorType::NONE;
}
