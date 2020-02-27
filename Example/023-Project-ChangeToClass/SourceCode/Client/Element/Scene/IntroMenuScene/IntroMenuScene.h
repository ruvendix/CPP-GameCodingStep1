// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ��Ʈ�� ȭ���� �޴� ���Դϴ�.
// =====================================================================================

#ifndef INTRO_MENU_SCENE_H__
#define INTRO_MENU_SCENE_H__

#include "Element\Scene.h"

class IntroMenu;

class IntroMenuScene final : public Scene
{
	NON_COPYABLE_CLASS(IntroMenuScene);
	FRIEND_WITH_HELPER(IntroMenuSceneHelper);
	FRAME_UPDATE_LIMITED(8);

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
	void OnTrigger_ExcuteMenu();

	TupleCompMenuInfo m_tupleLongestMenuInfo;
	std::vector<IntroMenu*> m_vecIntroMenu;
	Int32 m_selectedIntroMenuIdx = 0;
};

#endif