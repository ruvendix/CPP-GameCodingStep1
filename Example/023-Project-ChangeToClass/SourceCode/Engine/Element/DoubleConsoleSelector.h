// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �ܼ�â������ ���Ǵ� �������Դϴ�.
// �⺻ �����Ϳ��� ���� ���� ������ �ٸ� �����͸� ����� �� �ֽ��ϴ�.
// =====================================================================================

#ifndef DBL_CONSOLE_SELECTOR__H__
#define DBL_CONSOLE_SELECTOR__H__

#include "ConsoleSelector.h"

class DblConsoleSelector : public ConsoleSelector
{
public:
	using ConsoleSelector::ConsoleSelector;
	virtual ~DblConsoleSelector() = default;

	virtual void OnDrawSelector() const override;

	void setSecondSelectorOffsetPosX(Int32 x)
	{
		m_secondSelectorOffsetPos.X = x;
	}

	void setSecondShape(const std::string_view& szShape)
	{
		m_strSecondShape = szShape;
	}

private:
	std::string m_strSecondShape = "��";
	COORD m_secondSelectorOffsetPos{ 0, 0 };
};

#endif