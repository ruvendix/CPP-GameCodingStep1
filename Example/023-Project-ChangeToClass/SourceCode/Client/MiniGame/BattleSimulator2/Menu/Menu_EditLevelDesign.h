// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2���� ���Ǵ� �޴��Դϴ�.
// ���� �������� �����մϴ�.
// =====================================================================================

#ifndef MENU_EDIT_LEVEL_DESIGN_H__
#define MENU_EDIT_LEVEL_DESIGN_H__

#include "Element\Menu\Menu.h"

class BattleSimulator2_EditorScene;

class Menu_EditLevelDesign : public Menu
{
public:
#pragma region ������ �� �Ҹ���
	using Menu::Menu;

	Menu_EditLevelDesign() = default;
	virtual ~Menu_EditLevelDesign() = default;

	Menu_EditLevelDesign(const std::string_view& szNameTag,
		const COORD& pos, BattleSimulator2_EditorScene* pTargetScene);
#pragma endregion

	virtual EErrorType OnExcute() override;
	virtual void OnTrigger_Excute() override;

private:
	BattleSimulator2_EditorScene* m_pTargetScene = nullptr;
};

#endif