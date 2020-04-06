// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2에서 사용되는 메뉴입니다.
// 레벨 디자인을 불러옵니다.
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
	m_pTargetScene->getWorld()->Reset();
	m_pTargetScene->getLevelDesign()->LoadFile("BattleSimulator2.level");

	RESERVE_RENDERING_STRING(1.0f, std::bind(&Menu_LoadLevelDesign::OnTrigger_Excute, this));
	return EErrorType::NONE;
}

void Menu_LoadLevelDesign::OnTrigger_Excute()
{
	PUT_STRING(82, 28, "레벨 디자인 불러옴!");
}
