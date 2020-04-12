// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2���� ���Ǵ� �޴��Դϴ�.
// ���� ���� �������� �����ؼ� ������ �����մϴ�.
// =====================================================================================

#ifndef MENU_START_GAME_H__
#define MENU_START_GAME_H__

#include "Element\Menu\Menu.h"

class Menu_StartGame final : public Menu
{
	DECLARE_RTTI(Menu_StartGame, Menu);

public:
	using Menu::Menu;

#pragma region ������ �� �Ҹ���
	Menu_StartGame() = default;
	virtual ~Menu_StartGame() = default;
#pragma endregion

	virtual EErrorType OnExcute() override;
	virtual void OnTrigger_Excute() override;

private:
	void OnTrigger_GameStart();
};

#endif