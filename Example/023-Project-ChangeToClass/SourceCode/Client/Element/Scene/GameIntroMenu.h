// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ��Ʈ�� ȭ���� �޴� ���Դϴ�.
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