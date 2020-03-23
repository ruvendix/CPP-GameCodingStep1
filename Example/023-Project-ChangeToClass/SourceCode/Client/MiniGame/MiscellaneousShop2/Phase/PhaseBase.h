// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �⺻ �������Դϴ�.
// ����� ��ó�� ���� ��ȯ�ؾ� �մϴ�.
// �Ｎ���� ��ȯ�ϸ� ���� ������� ���װ� �߻��մϴ�.
// =====================================================================================

#ifndef PHASE_BASE_H__
#define PHASE_BASE_H__

#include "Element\GameElement.h"
#include "PhaseEnum.h"

class PhaseBase : public GameElem
{
public:
#pragma region ������ �� �Ҹ���
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
	PhaseBase* m_pNextPhase = nullptr; // ������� ��ȯ�� ����� �˰� �־�� �ؿ�!
};

#endif