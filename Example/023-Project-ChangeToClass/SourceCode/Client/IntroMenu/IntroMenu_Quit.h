// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 인트로 메뉴 씬에서 사용되는 보조 클래스입니다.
// 게임을 종료시킬 때 사용됩니다.
// =====================================================================================

#ifndef INTRO_MENU_QUIT_H__
#define INTRO_MENU_QUIT_H__

#include "Element\Menu\Menu.h"

class IntroMenu_Quit : public Menu
{
public:
	using Menu::Menu;

#pragma region 생성자 및 소멸자
	IntroMenu_Quit() = default;
	virtual ~IntroMenu_Quit() = default;
#pragma endregion

	virtual EErrorType OnExcute() override;
	virtual void OnTrigger_ExcuteMenu() override;
};

#endif