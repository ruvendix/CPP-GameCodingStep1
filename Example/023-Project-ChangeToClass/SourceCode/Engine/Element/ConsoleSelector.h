// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 콘솔창에서만 사용되는 셀렉터입니다.
// =====================================================================================

#ifndef CONSOLE_SELECTOR__H__
#define CONSOLE_SELECTOR__H__

#include "Common\CommonNecessary.h"
#include "Common\CommonType.h"

class ConsoleSelector
{
public:
	ConsoleSelector() = default;
	virtual ~ConsoleSelector() = default;

	void AddSelectorPosX(Int32 x);
	void AddSelectorPosY(Int32 y);

	virtual void OnDrawSelector() const;

	bool IsOriginPos() const
	{
		return ((m_selectorPos.X == 0) && (m_selectorPos.Y == 0));
	}

	const COORD& getSelectorPos() const
	{
		return m_selectorPos;
	}

	const COORD& getMinSelectorPos() const
	{
		return m_minSelectorPos;
	}

	const COORD& getMaxSelectorPos() const
	{
		return m_maxSelectorPos;
	}

	void setSelectorPos(const COORD& pos)
	{
		m_selectorPos = pos;
	}

	void setSelectorPos(Int32 x, Int32 y)
	{
		m_selectorPos.X = x;
		m_selectorPos.Y = y;
	}

	void setSelectorPosX(Int32 x)
	{
		m_selectorPos.X = x;
	}

	void setSelectorPosY(Int32 y)
	{
		m_selectorPos.Y = y;
	}

	void setMinSelectorPos(Int32 x, Int32 y)
	{
		m_minSelectorPos.X = x;
		m_minSelectorPos.Y = y;
	}

	void setMinSelectorPosX(Int32 x)
	{
		m_minSelectorPos.X = x;
	}

	void setMinSelectorPosY(Int32 y)
	{
		m_minSelectorPos.Y = y;
	}

	void setMaxSelectorPos(Int32 x, Int32 y)
	{
		m_maxSelectorPos.X = x;
		m_maxSelectorPos.Y = y;
	}

	void setMaxSelectorPosX(Int32 x)
	{
		m_maxSelectorPos.X = x;
	}

	void setMaxSelectorPosY(Int32 y)
	{
		m_maxSelectorPos.Y = y;
	}

	void setShape(const std::string_view& szShape)
	{
		m_strShape = szShape;
	}

private:
	std::string m_strShape = "▶";
	COORD m_selectorPos{ 0, 0 };
	COORD m_minSelectorPos{ 0, 0 };
	COORD m_maxSelectorPos{ 0, 0 };
};

#endif