// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 콘솔창에서만 사용되는 셀렉터입니다.
// 기본 셀렉터에서 일정 간격 떨어진 다른 셀렉터를 출력할 수 있습니다.
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
	std::string m_strSecondShape = "◀";
	COORD m_secondSelectorOffsetPos{ 0, 0 };
};

#endif