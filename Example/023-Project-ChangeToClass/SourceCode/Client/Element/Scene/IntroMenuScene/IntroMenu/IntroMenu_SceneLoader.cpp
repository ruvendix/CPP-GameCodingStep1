// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 인트로 메뉴 씬에서 사용되는 보조 클래스입니다.
// 열거형을 이용해서 씬을 로딩합니다.
// =====================================================================================

#include "PCH.h"
#include "IntroMenu_SceneLoader.h"

IntroMenu_SceneLoader::IntroMenu_SceneLoader(const std::string_view& szNameTag,
	const COORD& offsetCenterPos, EIntroMenu_SceneLoaderType sceneLoaderType) :
	IntroMenu(szNameTag, offsetCenterPos),
	m_sceneLoaderType(sceneLoaderType)
{

}

EErrorType IntroMenu_SceneLoader::OnExcute()
{
	switch (m_sceneLoaderType)
	{
	case EIntroMenu_SceneLoaderType::BATTLE_SIMULATOR:
	{

		break;
	}

	case EIntroMenu_SceneLoaderType::DIALOGUE_TREE:
	{

		break;
	}

	case EIntroMenu_SceneLoaderType::MISCELLANEOUS_SHOP2:
	{

		break;
	}

	default:
	{
		ERROR_HANDLER(EErrorType::UNKNOWN_INTRO_MENU_SCENE_LOADER_TYPE);
		break;
	}
	}

	return EErrorType();
}
