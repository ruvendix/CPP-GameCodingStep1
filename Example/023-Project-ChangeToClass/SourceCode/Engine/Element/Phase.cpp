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

#include "PCH.h"
#include "Phase.h"

Phase::Phase(const std::string_view& szNameTag, Int32 level) :
	GameElem(szNameTag),
	m_level(level)
{

}
