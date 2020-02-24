// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 게임 인트로 화면의 메뉴 씬입니다.
// =====================================================================================

#ifndef GAME_INTRO_MENU_SCENE_H__
#define GAME_INTRO_MENU_SCENE_H__

#include "Element\Scene.h"

// 인트로 메뉴 씬에서 사용되는 보조 클래스에요!
class GameIntroMenu
{
	HAS_NAME_TAG();

public:
#pragma region 생성자 및 소멸자
	GameIntroMenu() = default;
	virtual ~GameIntroMenu() = default;

	GameIntroMenu(const std::string_view& szNameTag, const COORD& offsetCenterPos);
#pragma endregion

	virtual EErrorType OnExcute();

	// 나중에 좌표 클래스 만들면 그걸로 적용할 예정!
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
	COORD m_pos; // 메뉴가 그려질 위치 (왼쪽 위 기준)
	COORD m_offsetCenterPos; // 중앙 정렬일 때의 오프셋 (사용 여부는 자유)
};

// 게임을 종료시키는 인트로 메뉴에요!
class GameIntroMenu_Quit : public GameIntroMenu
{
public:
	using GameIntroMenu::GameIntroMenu;

	GameIntroMenu_Quit() = default;
	virtual ~GameIntroMenu_Quit() = default;

	virtual EErrorType OnExcute() override;
};

// 씬을 불러올 수 있는 인트로 메뉴에요!
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