// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ܼ�â������ ���Ǵ� �������Դϴ�.
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
