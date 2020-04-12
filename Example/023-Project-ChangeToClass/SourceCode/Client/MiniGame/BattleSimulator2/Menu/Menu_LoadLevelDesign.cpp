// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2���� ���Ǵ� �޴��Դϴ�.
// ���� �������� �ҷ��ɴϴ�.
// =====================================================================================

#include "PCH.h"
#include "Menu_LoadLevelDesign.h"

#include "Controller\ConsoleController.h"
#include "Manager\TriggerTimerManager.h"

#include "Scene\BattleSimulator2_EditorScene.h"
#include "..\BattleSimulator2World.h"
#include "..\BattleSimulator2_LevelDesign.h"

Menu_LoadLevelDesign::Menu_LoadLevelDesign(const std::string_view& szNameTag,
	const COORD& pos, BattleSimulator2_EditorScene* pTargetScene) :
	Menu(szNameTag, pos),
	m_pTargetScene(pTargetScene)
{

}

EErrorType Menu_LoadLevelDesign::OnExcute()
{
	CHECK_NULLPTR(m_pTargetScene);
	if (m_pTargetScene->getLevelDesign()->LoadFile("BattleSimulator2.level") == EErrorType::LOAD_FILE_FAIL)
	{
		return EErrorType::LOAD_FILE_FAIL;
	}

	RESERVE_RENDERING_STRING(1.0f, std::bind(&Menu_LoadLevelDesign::OnTrigger_Excute, this));
	return EErrorType::NOTHING;
}

void Menu_LoadLevelDesign::OnTrigger_Excute()
{
	PUT_STRING(82, 28, "���� ������ �ҷ���!");
}
