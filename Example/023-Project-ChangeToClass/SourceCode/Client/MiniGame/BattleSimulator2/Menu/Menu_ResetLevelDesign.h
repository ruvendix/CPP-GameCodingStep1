// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2���� ���Ǵ� �޴��Դϴ�.
// ���� �������� �ʱ�ȭ�մϴ�.
// =====================================================================================

#ifndef MENU_RESET_LEVEL_DESIGN_H__
#define MENU_RESET_LEVEL_DESIGN_H__

#include "Element\Menu\Menu.h"

class BattleSimulator2_EditorScene;

class Menu_ResetLevelDesign : public Menu
{
public:
#pragma region ������ �� �Ҹ���
	using Menu::Menu;

	Menu_ResetLevelDesign() = default;
	virtual ~Menu_ResetLevelDesign() = default;

	Menu_ResetLevelDesign(const std::string_view& szNameTag,
		const COORD& pos, BattleSimulator2_EditorScene* pTargetScene);
#pragma endregion

	virtual EErrorType OnExcute() override;
	virtual void OnTrigger_Excute() override;

private:
	BattleSimulator2_EditorScene* m_pTargetScene = nullptr;
};

#endif