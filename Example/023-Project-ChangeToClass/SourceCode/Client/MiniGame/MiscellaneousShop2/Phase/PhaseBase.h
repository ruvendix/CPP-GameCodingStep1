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

	bool HasNextPhase() const
	{
		return (m_pNextPhase != nullptr);
	}

	PhaseBase* getNextPhase() const
	{
		return m_pNextPhase;
	}

	EPhaseType getCurrentPhaseType() const
	{
		return m_currentPhaseType;
	}

	Int32 getLevel() const
	{
		return m_level;
	}

	void setCurrentPhaseType(EPhaseType phaseType)
	{
		m_currentPhaseType = phaseType;
	}

	void setNextPhase(PhaseBase* pNextPhase)
	{
		m_pNextPhase = pNextPhase;
	}

	void setLevel(Int32 level)
	{
		m_level = level;
	}

private:
	Int32 m_level = 0;
	EPhaseType m_currentPhaseType = EPhaseType::NONE;
	PhaseBase* m_pNextPhase = nullptr; // ������� ��ȯ�� ����� �˰� �־�� �ؿ�!
};

#endif