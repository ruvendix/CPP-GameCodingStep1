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

#ifndef PHASE_BASE_H__
#define PHASE_BASE_H__

#include "Element\GameElement.h"
#include "PhaseEnum.h"

class PhaseBase : public GameElem
{
public:
#pragma region 생성자 및 소멸자
	using GameElem::GameElem;
	virtual ~PhaseBase() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;

	void AddSelectorPosX(Int32 x)
	{
		m_selectorPos.X += x;
		m_selectorPos.X = math::Clamp(m_selectorPos.X, m_minSelectorPos.X, m_maxSelectorPos.X);
	}

	void AddSelectorPosY(Int32 y)
	{
		m_selectorPos.Y += y;
		m_selectorPos.Y = math::Clamp(m_selectorPos.Y, m_minSelectorPos.Y, m_maxSelectorPos.Y);
	}

	bool HasNextPhase() const
	{
		return (m_pNextPhase != nullptr);
	}

	PhaseBase* getNextPhase() const
	{
		return m_pNextPhase;
	}

	const COORD& getSelectorPos() const
	{
		return m_selectorPos;
	}

	EPhaseType getCurrentPhaseType() const
	{
		return m_currentPhaseType;
	}

	const COORD& getMinSelectorPos() const
	{
		return m_minSelectorPos;
	}

	const COORD& getMaxSelectorPos() const
	{
		return m_maxSelectorPos;
	}

	void setNextPhase(PhaseBase* pNextPhase)
	{
		m_pNextPhase = pNextPhase;
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

	void setCurrentPhaseType(EPhaseType phaseType)
	{
		m_currentPhaseType = phaseType;
	}

private:
	COORD m_selectorPos{ 0, 0 };
	COORD m_minSelectorPos{ 0, 0 };
	COORD m_maxSelectorPos{ 0, 0 };

	EPhaseType m_currentPhaseType = EPhaseType::NONE;
	PhaseBase* m_pNextPhase = nullptr; // 페이즈는 전환할 페이즈를 알고 있어야 해요!
};

#endif