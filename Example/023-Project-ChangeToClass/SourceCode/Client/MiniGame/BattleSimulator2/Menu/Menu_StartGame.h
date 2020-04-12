// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2에서 사용되는 메뉴입니다.
// 현재 레벨 디자인을 적용해서 게임을 시작합니다.
// =====================================================================================

#ifndef MENU_START_GAME_H__
#define MENU_START_GAME_H__

#include "Element\Menu\Menu.h"

class Menu_StartGame final : public Menu
{
	DECLARE_RTTI(Menu_StartGame, Menu);

public:
	using Menu::Menu;

#pragma region 생성자 및 소멸자
	Menu_StartGame() = default;
	virtual ~Menu_StartGame() = default;
#pragma endregion

	virtual EErrorType OnExcute() override;
	virtual void OnTrigger_Excute() override;

private:
	void OnTrigger_GameStart();
};

#endif