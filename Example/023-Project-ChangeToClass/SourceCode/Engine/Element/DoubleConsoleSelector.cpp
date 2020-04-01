// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ܼ�â������ ���Ǵ� �������Դϴ�.
// �⺻ �����Ϳ��� ���� ���� ������ �ٸ� �����͸� ����� �� �ֽ��ϴ�.
// =====================================================================================
#include "PCH.h"
#include "DoubleConsoleSelector.h"

#include "Controller\ConsoleController.h"

void DblConsoleSelector::OnDrawSelector() const
{
	ConsoleSelector::OnDrawSelector();
	PUT_STRING(getSelectorPos().X + m_secondSelectorOffsetPos.X, getSelectorPos().Y + m_secondSelectorOffsetPos.Y, m_strSecondShape.c_str());
}
