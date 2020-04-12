// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 기본 페이즈입니다.
// 페이즈도 씬처럼 지연 전환해야 합니다.
// 즉석에서 전환하면 현재 페이즈에서 버그가 발생합니다.
// =====================================================================================

#ifndef PHASE_H__
#define PHASE_H__

#include "Element\GameElement.h"

class Phase : public GameElem
{
	DECLARE_RTTI(Phase, GameElem);

public:
#pragma region 생성자 및 소멸자
	Phase() = default;
	virtual ~Phase() = default;

	Phase(const std::string_view& szNameTag, Int32 level);
#pragma endregion

	Int32 getLevel() const
	{
		return m_level;
	}

private:
	Int32 m_level = 0;
};

#endif