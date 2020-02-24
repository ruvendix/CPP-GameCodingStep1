// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ��Ʈ�� ȭ���� �޴� ���Դϴ�.
// =====================================================================================

#ifndef GAME_INTRO_MENU_SCENE_H__
#define GAME_INTRO_MENU_SCENE_H__

#include "Element\Scene.h"

// ��Ʈ�� �޴� ������ ���Ǵ� ���� Ŭ��������!
class GameIntroMenu
{
	HAS_NAME_TAG();

public:
#pragma region ������ �� �Ҹ���
	GameIntroMenu() = default;
	virtual ~GameIntroMenu() = default;

	GameIntroMenu(const std::string_view& szNameTag, const COORD& offsetCenterPos);
#pragma endregion

	virtual EErrorType OnExcute();

	// ���߿� ��ǥ Ŭ���� ����� �װɷ� ������ ����!
	const COORD& getPos() const
	{
		return m_pos;
	}

	void setPos(const COORD& pos)
	{
		m_pos = pos;
	}

	const COORD& getOffsetCenterPos() const
	{
		return m_offsetCenterPos;
	}

	void setOffsetCenterPos(Int32 x, Int32 y)
	{
		m_offsetCenterPos.X = x;
		m_offsetCenterPos.Y = y;
	}

private:
	COORD m_pos; // �޴��� �׷��� ��ġ (���� �� ����)
	COORD m_offsetCenterPos; // �߾� ������ ���� ������ (��� ���δ� ����)
};

// ������ �����Ű�� ��Ʈ�� �޴�����!
class GameIntroMenu_Quit : public GameIntroMenu
{
public:
	using GameIntroMenu::GameIntroMenu;

	GameIntroMenu_Quit() = default;
	virtual ~GameIntroMenu_Quit() = default;

	virtual EErrorType OnExcute() override;
};

// ���� �ҷ��� �� �ִ� ��Ʈ�� �޴�����!
class GameIntroMenu_SceneLoader : public GameIntroMenu
{
public:
	using GameIntroMenu::GameIntroMenu;

	GameIntroMenu_SceneLoader() = default;
	virtual ~GameIntroMenu_SceneLoader() = default;

	virtual EErrorType OnExcute() override;

	void setLoadSceneName(const std::string_view& szLoadSceneName)
	{
		m_strLoadSceneName = szLoadSceneName;
	}

private:
	std::string m_strLoadSceneName;
};

class GameIntroMenuScene final : public Scene
{
	NON_COPYABLE_CLASS(GameIntroMenuScene);
	FRIEND_WITH_HELPER(GameIntroMenuSceneHelper);
	FRAME_UPDATE_LIMITED(5);

public:
	using Scene::Scene;
	using TupleCompMenuInfo = std::tuple<std::string, COORD, bool>;

	GameIntroMenuScene() = default;
	virtual ~GameIntroMenuScene() = default;

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;

	void OnTrigger_ExcuteMenu();

private:
	TupleCompMenuInfo m_tupleLongestMenuInfo;
	std::vector<GameIntroMenu*> m_vecGameIntroMenu;
	Int32 m_selectedGameIntroMenuIdx = 0;
};

#endif