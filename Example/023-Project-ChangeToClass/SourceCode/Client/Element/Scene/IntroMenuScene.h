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
#include "Controller\ConsoleControllerEnum.h"
#include "Element\DoubleConsoleSelector.h"

DECLARE_LOG_CATEGORY(IntroMenuScene);

class IntroMenu;

class IntroMenuScene final : public Scene
{
	NON_COPYABLE_CLASS(IntroMenuScene);
	FRIEND_WITH_HELPER(IntroMenuSceneHelper);
	INPUT_FPS_LIMITED(8);

public:
	using Scene::Scene;
	using TupleCompMenu = std::tuple<std::string, COORD, bool>;

	IntroMenuScene() = default;
	virtual ~IntroMenuScene() = default;

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;

private:
	void OnTrigger_ChangeRandomColorToTitle();
	void OnTrigger_ExcuteMenu();

	std::unique_ptr<DblConsoleSelector> m_spDblConsoleSelector;
	std::vector<std::shared_ptr<IntroMenu>> m_vecIntroMenu;
	EConsoleOutputColorType m_titleColorType = EConsoleOutputColorType::WHITE;
	TupleCompMenu m_tupleLongestMenuInfo;
	Int32 m_selectedIntroMenuIdx = 0;
};

#endif