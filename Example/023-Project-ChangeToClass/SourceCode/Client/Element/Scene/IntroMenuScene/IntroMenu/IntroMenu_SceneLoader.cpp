// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʈ�� �޴� ������ ���Ǵ� ���� Ŭ�����Դϴ�.
// �������� �̿��ؼ� ���� �ε��մϴ�.
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
