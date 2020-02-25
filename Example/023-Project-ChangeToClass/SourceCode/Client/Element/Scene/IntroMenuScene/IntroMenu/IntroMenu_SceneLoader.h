// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʈ�� �޴� ������ ���Ǵ� ���� Ŭ�����Դϴ�.
// �������� �̿��ؼ� ���� �ε��մϴ�.
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
#pragma region ������ �� �Ҹ���
	IntroMenu_SceneLoader() = default;
	virtual ~IntroMenu_SceneLoader() = default;

	IntroMenu_SceneLoader(const std::string_view& szNameTag, const COORD& offsetCenterPos, EIntroMenu_SceneLoaderType sceneLoaderType);
#pragma endregion

	virtual EErrorType OnExcute() override;

private:
	EIntroMenu_SceneLoaderType m_sceneLoaderType = EIntroMenu_SceneLoaderType::UNKNOWN;
};

#endif