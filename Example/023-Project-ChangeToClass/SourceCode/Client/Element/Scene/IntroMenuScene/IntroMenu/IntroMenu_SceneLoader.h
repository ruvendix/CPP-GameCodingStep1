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

#include "./IntroMenu.h"

enum class EIntroMenu_SceneLoaderType
{
	UNKNOWN = 0,
	BATTLE_SIMULATOR,
	DIALOGUE_TREE,
	MISCELLANEOUS_SHOP2
};

class IntroMenu_SceneLoader : public IntroMenu
{
public:
#pragma region 생성자 및 소멸자
	IntroMenu_SceneLoader() = default;
	virtual ~IntroMenu_SceneLoader() = default;

	IntroMenu_SceneLoader(const std::string_view& szNameTag, const COORD& offsetCenterPos, EIntroMenu_SceneLoaderType sceneLoaderType);
#pragma endregion

	virtual EErrorType OnExcute() override;

private:
	EIntroMenu_SceneLoaderType m_sceneLoaderType = EIntroMenu_SceneLoaderType::UNKNOWN;
};

#endif