// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2���� ���Ǵ� �޴��Դϴ�.
// ���� ���� �������� �����ؼ� ������ �����մϴ�.
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
	PUT_STRING(82, 28, "���� ���� ���������� ������ �����ҰԿ�!");
}

void Menu_StartGame::OnTrigger_GameStart()
{
	InputController::I()->EnableInput();
	BattleSimulator2_DataCollector::I()->Finalize();
	SceneMgr::I()->CreateScene<BattleSimulator2_GameScene>(ECreateType::NEXT);
}
