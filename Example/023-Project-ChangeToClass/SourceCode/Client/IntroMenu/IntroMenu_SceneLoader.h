// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 인트로 메뉴 씬에서 사용되는 보조 클래스입니다.
// 열거형을 이용해서 씬을 로딩합니다.
// =====================================================================================

#ifndef INTRO_MENU_SCENE_LOADER_H__
#define INTRO_MENU_SCENE_LOADER_H__

#include "Element\Menu\Menu.h"

enum class EMiniGameSceneType
{
	UNKNOWN = 0,
	BATTLE_SIMULATOR2,
	DIALOG_TREE,
	MISCELLANEOUS_SHOP2
};

class IntroMenu_SceneLoader : public Menu
{
public:
	using Menu::Menu;

#pragma region 생성자 및 소멸자
	IntroMenu_SceneLoader() = default;
	virtual ~IntroMenu_SceneLoader() = default;

	IntroMenu_SceneLoader(const std::string_view& szNameTag,
		const COORD& pos, const COORD& offsetCenterPos, EMiniGameSceneType miniGameSceneType);
#pragma endregion

	virtual EErrorType OnExcute() override;
	virtual void OnTrigger_Excute() override;

private:
	EMiniGameSceneType m_selectedSceneType = EMiniGameSceneType::UNKNOWN;
};

#endif