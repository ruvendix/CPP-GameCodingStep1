// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ������ ���� �� ��ȯ ���� ó���ϰ� �����մϴ�.
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
	���ϴ� ����� �����ؼ� ����մϴ�.
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

			// ���� ������� �Ѿ ���� �������� ��ǥ�� �����ؾ� �ϴ��� Ȯ���ؾ� �ؿ�!
			if (m_spCurrentPhase->getLevel() < m_spNextPhase->getLevel())
			{
				ConsoleController::I()->PushBackupConsoleSelector();
			}

			// ��ȯ�� ������ ���� �ʱ�ȭ�� �Ϸ�� ���·� ��ȯ�Ǿ�� �ؿ�!
			if (m_spNextPhase->OnInitialize() == EErrorType::INIT_FAIL)
			{
				DEFAULT_ERROR_HANDLER(EErrorType::INIT_FAIL);
			}
		}
	}

	/*
	������ �̸��� ������ Ÿ�Կ��� ������ ����մϴ�.
	*/
	template <typename TPhase>
	void CreatePhase(ECreateType createType, Int32 level)
	{
		std::string strSceneName = typeid(TPhase).name();
		strSceneName = strSceneName.substr(5 + 1, _TRUNCATE); // 5 + 1�� "class" + " "
		CreatePhase<TPhase>(strSceneName, createType, level);
	}

private:
	std::shared_ptr<Phase> m_spCurrentPhase;
	std::unique_ptr<Phase> m_spNextPhase;
};

#endif