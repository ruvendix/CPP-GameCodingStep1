// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �� ���� �� ��ȯ ���� ó���ϰ� �����մϴ�.
// =====================================================================================

#ifndef SCENE_MGR__H__
#define SCENE_MGR__H__

#include "Common\CommonType.h"
#include "Common\CommonEnum.h"
#include "Common\CommonMacro.h"
#include "Controller\ConsoleController.h"
#include "Element\Scene.h"

DECLARE_LOG_CATEGORY(SceneMgr);

class SceneMgr final
{
	DECLARE_PHOENIX_SINGLETON(SceneMgr);

public:
	EErrorType Flip();

	bool IsGotoNextScene() const
	{
		return (m_spNextScene != nullptr);
	}

	std::shared_ptr<Scene> getCurrentScene() const
	{
		return m_spCurrentScene;
	}

	/*
	���ϴ� ���� �����ؼ� ����մϴ�.
	*/
	template <typename TScene>
	void CreateScene(const std::string_view& szSceneName, ECreateType createType)
	{
		if (createType == ECreateType::CURRENT)
		{
			if (m_spCurrentScene != nullptr)
			{
				DEFAULT_ERROR_HANDLER(EErrorType::OVERLAPPED_SCENE, m_spCurrentScene->getNameTag());
				return;
			}

			m_spCurrentScene = std::make_shared<TScene>(szSceneName);
			if (m_spCurrentScene->OnInitialize() == EErrorType::INIT_FAIL)
			{
				DEFAULT_ERROR_HANDLER(EErrorType::INIT_FAIL);
			}
		}
		else
		{
			m_spNextScene = std::make_unique<TScene>(szSceneName);

			// ��ȯ�� ������ ���� �ʱ�ȭ�� �Ϸ�� ���·� ��ȯ�Ǿ�� �ؿ�!
			if (m_spNextScene->OnInitialize() == EErrorType::INIT_FAIL)
			{
				DEFAULT_ERROR_HANDLER(EErrorType::INIT_FAIL);
			}

			if (m_spNextScene->OnPostInitialize() == EErrorType::INIT_FAIL)
			{
				DEFAULT_ERROR_HANDLER(EErrorType::INIT_FAIL);
			}
		}
	}

	/*
	���� �̸��� �� Ÿ������ �����ؼ� �����ϰ� ����մϴ�.
	*/
	template <typename TScene>
	void CreateScene(ECreateType createType)
	{
		std::string strSceneName = typeid(TScene).name();
		strSceneName = strSceneName.substr(5 + 1, _TRUNCATE); // 5 + 1�� "class" + " "
		CreateScene<TScene>(strSceneName, createType);
	}

private:
	std::shared_ptr<Scene> m_spCurrentScene;
	std::unique_ptr<Scene> m_spNextScene;
};

#endif