// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 페이즈 생성 및 전환 등을 처리하고 관리합니다.
// =====================================================================================

#ifndef PHASE_MGR__H__
#define PHASE_MGR__H__

#include "Common\CommonType.h"
#include "Common\CommonEnum.h"
#include "Common\CommonMacro.h"
#include "Controller\ConsoleController.h"
#include "Element\Phase.h"

DECLARE_LOG_CATEGORY(PhaseMgr);

class PhaseMgr final
{
	DECLARE_PHOENIX_SINGLETON(PhaseMgr);

public:
	EErrorType Flip();

	void Reset()
	{
		m_spCurrentPhase = nullptr;
		m_spNextPhase = nullptr;
	}

	bool IsGotoNextPhase() const
	{
		return (m_spNextPhase != nullptr);
	}

	std::shared_ptr<Phase> getCurrentPhase() const
	{
		return m_spCurrentPhase;
	}

	/*
	원하는 페이즈를 생성해서 등록합니다.
	*/
	template <typename TPhase>
	void CreatePhase(const std::string_view& szSceneName, ECreateType createType, Int32 level)
	{
		if (createType == ECreateType::CURRENT)
		{
			if (m_spCurrentPhase != nullptr)
			{
				DEFAULT_ERROR_HANDLER(EErrorType::OVERLAPPED_SCENE, m_spCurrentPhase->getNameTag());
				return;
			}

			m_spCurrentPhase = std::make_shared<TPhase>(szSceneName, level);
			if (m_spCurrentPhase->OnInitialize() == EErrorType::INIT_FAIL)
			{
				DEFAULT_ERROR_HANDLER(EErrorType::INIT_FAIL);
			}
		}
		else
		{
			m_spNextPhase = std::make_unique<TPhase>(szSceneName, level);

			// 다음 페이즈로 넘어갈 때는 셀렉터의 좌표를 복원해야 하는지 확인해야 해요!
			if (m_spCurrentPhase->getLevel() < m_spNextPhase->getLevel())
			{
				ConsoleController::I()->PushBackupConsoleSelector();
			}

			// 전환될 예정인 씬은 초기화가 완료된 상태로 전환되어야 해요!
			if (m_spNextPhase->OnInitialize() == EErrorType::INIT_FAIL)
			{
				DEFAULT_ERROR_HANDLER(EErrorType::INIT_FAIL);
			}
		}
	}

	/*
	페이즈 이름을 페이즈 타입에서 가져와 등록합니다.
	*/
	template <typename TPhase>
	void CreatePhase(ECreateType createType, Int32 level)
	{
		std::string strSceneName = typeid(TPhase).name();
		strSceneName = strSceneName.substr(5 + 1, _TRUNCATE); // 5 + 1은 "class" + " "
		CreatePhase<TPhase>(strSceneName, createType, level);
	}

private:
	std::shared_ptr<Phase> m_spCurrentPhase;
	std::unique_ptr<Phase> m_spNextPhase;
};

#endif