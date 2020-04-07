// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʈ�� �޴� ������ ���ƿ��� ���ݴϴ�.
// ���� ���ӿ��� ��� �����մϴ�.
// =====================================================================================

#ifndef INTRO_MENU_COME_BACK_H__
#define INTRO_MENU_COME_BACK_H__

#include "Element\Menu\Menu.h"

class IntroMenu_ComeBack : public Menu
{
public:
	using Menu::Menu;

#pragma region ������ �� �Ҹ���
	virtual ~IntroMenu_ComeBack() = default;
#pragma endregion

	virtual EErrorType OnExcute() override;
};

#endif