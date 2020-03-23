// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �� ���� �� ��ȯ ���� ó�����ִ� �Ŵ����Դϴ�.
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
	���ϴ� �� Ÿ������ ���� �����ϰ� ����մϴ�.
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

			// ��ȯ�� ������ ���� �ʱ�ȭ�� �Ϸ�� ���·� ��ȯ�Ǿ�� �ؿ�!
			if (m_pNextScene->OnInitialize() == EErrorType::INIT_FAILED)
			{
				ErrorHandler::ToString(EErrorType::INIT_FAILED);
			}
		}
	}

	/*
	���� �̸��� �� Ÿ������ �����ؼ� �����ϰ� ����մϴ�.
	*/
	template <typename TScene>
	void CreateScene(ESceneType sceneType)
	{
		std::string strSceneName = typeid(TScene).name();
		strSceneName = strSceneName.substr(5 + 1, _TRUNCATE); // 5 + 1�� "class" + " "
		CreateScene<TScene>(strSceneName, sceneType);
	}

private:
	Scene* m_pCurrentScene = nullptr;
	Scene* m_pNextScene = nullptr;
};

#endif