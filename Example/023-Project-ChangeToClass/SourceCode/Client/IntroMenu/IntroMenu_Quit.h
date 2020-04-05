// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʈ�� �޴� ������ ���Ǵ� ���� Ŭ�����Դϴ�.
// ������ �����ų �� ���˴ϴ�.
// =====================================================================================

#ifndef INTRO_MENU_QUIT_H__
#define INTRO_MENU_QUIT_H__

#include "Element\Menu\Menu.h"

class IntroMenu_Quit : public Menu
{
public:
	using Menu::Menu;

#pragma region ������ �� �Ҹ���
	IntroMenu_Quit() = default;
	virtual ~IntroMenu_Quit() = default;
#pragma endregion

	virtual EErrorType OnExcute() override;
	virtual void OnTrigger_ExcuteMenu() override;
};

#endif