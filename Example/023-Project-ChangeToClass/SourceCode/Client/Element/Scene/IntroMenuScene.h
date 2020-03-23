// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 게임 인트로 화면의 메뉴 씬입니다.
// =====================================================================================

#ifndef INTRO_MENU_SCENE_H__
#define INTRO_MENU_SCENE_H__

#include "Element\Scene.h"
#include "Controller\ConsoleControllerEnum.h"

DECLARE_LOG_CATEGORY(IntroMenuScene);

class IntroMenu;

class IntroMenuScene final : public Scene
{
	NON_COPYABLE_CLASS(IntroMenuScene);
	FRIEND_WITH_HELPER(IntroMenuSceneHelper);
	FRAME_UPDATE_LIMITED(3);

public:
	using Scene::Scene;
	using TupleCompMenuInfo = std::tuple<std::string, COORD, bool>;

	IntroMenuScene() = default;
	virtual ~IntroMenuScene() = default;

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;

private:
	void OnTrigger_ChangeRandomColorToTitle();
	void OnTrigger_ExcuteMenu();

	EConsoleOutputColorType m_titleColorType = EConsoleOutputColorType::WHITE;
	TupleCompMenuInfo m_tupleLongestMenuInfo;
	std::vector<IntroMenu*> m_vecIntroMenu;
	Int32 m_selectedIntroMenuIdx = 0;
};

#endif