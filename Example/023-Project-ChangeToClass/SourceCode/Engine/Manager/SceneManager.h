// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 씬 생성 및 전환 등을 처리해주는 매니저입니다.
// =====================================================================================

#ifndef SCENE_MANAGER__H__
#define SCENE_MANAGER__H__

#include "Common\CommonType.h"
#include "Element\Scene.h"

DECLARE_LOG_CATEGORY(SceneMgr);

enum class ESceneType : Int32
{
	CURRENT = 0,
	NEXT,
};

class SceneMgr final
{
	DECLARE_PHOENIX_SINGLETON(SceneMgr);

public:
	void Finalize();
	void FlipCurrentScene();

	bool IsGotoNextScene() const
	{
		return (m_pNextScene != nullptr);
	}

	Scene* getCurrentScene() const
	{
		CHECK_NULLPTR(m_pCurrentScene);
		return m_pCurrentScene;
	}

	/*
	원하는 씬 타입으로 씬을 생성하고 등록합니다.
	*/
	template <typename TScene>
	void CreateScene(const std::string_view& szSceneName, ESceneType sceneType)
	{
		if (sceneType == ESceneType::CURRENT)
		{
			if (m_pCurrentScene != nullptr)
			{
				ERROR_HANDLER(EErrorType::OVERLAPPED_SCENE, m_pCurrentScene->getNameTag());
				return;
			}

			m_pCurrentScene = trace_new TScene(szSceneName);

			if (m_pCurrentScene->OnInitialize() == EErrorType::INIT_FAILED)
			{
				ErrorHandler::ToString(EErrorType::INIT_FAILED);
			}
		}
		else
		{
			SAFE_DELETE(m_pNextScene);
			m_pNextScene = trace_new TScene(szSceneName);

			// 전환될 예정인 씬은 초기화가 완료된 상태로 전환되어야 해요!
			if (m_pNextScene->OnInitialize() == EErrorType::INIT_FAILED)
			{
				ErrorHandler::ToString(EErrorType::INIT_FAILED);
			}
		}
	}

	/*
	씬의 이름을 씬 타입으로 설정해서 생성하고 등록합니다.
	*/
	template <typename TScene>
	void CreateScene(ESceneType sceneType)
	{
		std::string strSceneName = typeid(TScene).name();
		strSceneName = strSceneName.substr(5 + 1, _TRUNCATE); // 5 + 1은 "class" + " "
		CreateScene<TScene>(strSceneName, sceneType);
	}

private:
	Scene* m_pCurrentScene = nullptr;
	Scene* m_pNextScene = nullptr;
};

#endif