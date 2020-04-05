// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 씬 생성 및 전환 등을 처리하고 관리합니다.
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
	원하는 씬을 생성해서 등록합니다.
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

			// 전환될 예정인 씬은 초기화가 완료된 상태로 전환되어야 해요!
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
	씬의 이름을 씬 타입으로 설정해서 생성하고 등록합니다.
	*/
	template <typename TScene>
	void CreateScene(ECreateType createType)
	{
		std::string strSceneName = typeid(TScene).name();
		strSceneName = strSceneName.substr(5 + 1, _TRUNCATE); // 5 + 1은 "class" + " "
		CreateScene<TScene>(strSceneName, createType);
	}

private:
	std::shared_ptr<Scene> m_spCurrentScene;
	std::unique_ptr<Scene> m_spNextScene;
};

#endif