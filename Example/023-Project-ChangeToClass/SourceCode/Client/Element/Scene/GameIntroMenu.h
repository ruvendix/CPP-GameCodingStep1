// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 게임 인트로 화면의 메뉴 씬입니다.
// =====================================================================================

#ifndef GAME_INTRO_MENU_H__
#define GAME_INTRO_MENU_H__

#include "Element\Scene.h"

class GameIntroMenuScene final : public Scene
{
	NON_COPYABLE_CLASS(GameIntroMenuScene);
	FRIEND_WITH_HELPER(GameIntroMenuSceneHelper);

public:
	using Scene::Scene;

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;
};

#endif