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

class SceneMgr final
{
	DECLARE_SINGLETON(SceneMgr);

public:
	void DeleteScene();
	void FlipCurrentScene();

	bool IsGotoNextScene() const
	{
		return (m_bGotoNextScene == true);
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
				DEBUG_LOG_CATEGORY(SceneMgr, "%s ���� �̹� �����մϴ�!", m_pCurrentScene->getNameTag().data());
				return;
			}

			m_pCurrentScene = new TScene(szSceneName);

			if (m_pCurrentScene->OnInitialize() == EErrorType::INIT_FAILED)
			{
				ErrorHandler::ShowError(EErrorType::INIT_FAILED);
			}
		}
		else
		{
			SAFE_DELETE(m_pNextScene);
			m_pNextScene = new TScene(szSceneName);

			// ��ȯ�� ������ ���� �ʱ�ȭ�� �Ϸ�� ���·� ��ȯ�Ǿ�� �ؿ�!
			if (m_pNextScene->OnInitialize() == EErrorType::INIT_FAILED)
			{
				ErrorHandler::ShowError(EErrorType::INIT_FAILED);
			}

			m_bGotoNextScene = true;
		}
	}

	/*
	���� �̸��� �� Ÿ������ �����ؼ� �����ϰ� ����մϴ�.
	*/
	template <typename TScene>
	void CreateScene(ESceneType sceneType)
	{
		CreateScene<TScene>(TO_STRING(TScene), sceneType);
	}

private:
	Scene* m_pCurrentScene = nullptr;
	Scene* m_pNextScene = nullptr;
	bool m_bGotoNextScene = false;
};

#endif