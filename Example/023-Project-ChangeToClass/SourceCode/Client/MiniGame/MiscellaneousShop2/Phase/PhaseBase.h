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
	PhaseBase* m_pNextPhase = nullptr; // 페이즈는 전환할 페이즈를 알고 있어야 해요!
};

#endif