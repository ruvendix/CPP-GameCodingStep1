// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2���� ���Ǵ� �޴��Դϴ�.
// ���� �������� �����մϴ�.
// =====================================================================================

#include "PCH.h"
#include "Menu_SaveLevelDesign.h"

#include "Controller\ConsoleController.h"
#include "Manager\TriggerTimerManager.h"

#include "Scene\BattleSimulator2_EditorScene.h"
#include "..\BattleSimulator2_LevelDesign.h"

Menu_SaveLevelDesign::Menu_SaveLevelDesign(const std::string_view& szNameTag,
	const COORD& pos, BattleSimulator2_EditorScene* pTargetScene) :
	Menu(szNameTag, pos),
	m_pTargetScene(pTargetScene)
{

}

EErrorType Menu_SaveLevelDesign::OnExcute()
{
	CHECK_NULLPTR(m_pTargetScene);
	m_pTargetScene->getLevelDesign()->SaveFile("BattleSimulator2.level");

	RESERVE_RENDERING_STRING(1.0f, std::bind(&Menu_SaveLevelDesign::OnTrigger_Excute, this));
	return EErrorType::NOTHING;
}

void Menu_SaveLevelDesign::OnTrigger_Excute()
{
	PUT_STRING(82, 28, "���� ������ ����!");
}
