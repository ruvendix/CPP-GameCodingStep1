// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 콘솔창에서만 사용되는 셀렉터입니다.
// =====================================================================================
#include "PCH.h"
#include "ConsoleSelector.h"

#include "Common\CommonMacro.h"
#include "Math\Math.h"
#include "Controller\ConsoleController.h"

void ConsoleSelector::AddSelectorPosX(Int32 x)
{
	m_selectorPos.X += x;
	m_selectorPos.X = math::Clamp(m_selectorPos.X, m_minSelectorPos.X, m_maxSelectorPos.X);
}

void ConsoleSelector::AddSelectorPosY(Int32 y)
{
	m_selectorPos.Y += y;
	m_selectorPos.Y = math::Clamp(m_selectorPos.Y, m_minSelectorPos.Y, m_maxSelectorPos.Y);
}

void ConsoleSelector::OnDrawSelector() const
{
	PRINTF(m_selectorPos.X, m_selectorPos.Y, m_strShape.c_str());
}
