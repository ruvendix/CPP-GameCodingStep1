// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2에서 사용되는 메뉴입니다.
// 현재 레벨 디자인을 적용해서 게임을 시작합니다.
// =====================================================================================

#include "PCH.h"
#include "Menu_StartGame.h"

#include "Controller\ConsoleController.h"
#include "Controller\InputController.h"
#include "Manager\SceneManager.h"
#include "Manager\TriggerTimerManager.h"
#include "Timer\TriggerTimer.h"

#include "Scene\BattleSimulator2_GameScene.h"
#include "..\BattleSimulator2_DataCollector.h"

EErrorType Menu_StartGame::OnExcute()
{
	InputController::I()->DisableInput();

	TriggerTimerMgr::I()->AddTriggerTimer("GameStart_Menu_StartGame",
		1.0f, 0.0f, this, &Menu_StartGame::OnTrigger_GameStart, false, false);

	RESERVE_RENDERING_STRING(1.0f, std::bind(&Menu_StartGame::OnTrigger_Excute, this));
	return EErrorType::NOTHING;
}

void Menu_StartGame::OnTrigger_Excute()
{
	PUT_STRING(82, 28, "현재 레벨 디자인으로 게임을 시작할게요!");
}

void Menu_StartGame::OnTrigger_GameStart()
{
	InputController::I()->EnableInput();
	BattleSimulator2_DataCollector::I()->Finalize();
	SceneMgr::I()->CreateScene<BattleSimulator2_GameScene>(ECreateType::NEXT);
}
