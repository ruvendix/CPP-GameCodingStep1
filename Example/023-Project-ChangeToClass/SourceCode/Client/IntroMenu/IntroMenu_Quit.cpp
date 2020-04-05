// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʈ�� �޴� ������ ���Ǵ� ���� Ŭ�����Դϴ�.
// ������ �����ų �� ���˴ϴ�.
// =====================================================================================

#include "PCH.h"
#include "IntroMenu_Quit.h"

#include "Manager\TriggerTimerManager.h"
#include "Controller\InputController.h"

#include "Context\GameContext.h"

EErrorType IntroMenu_Quit::OnExcute()
{
	InputController::I()->DisableInput();
	TriggerTimerMgr::I()->AddTriggerTimer("Excute_IntroMenu_Quit",
		1.0f, 0.0f, this, &IntroMenu_Quit::OnTrigger_ExcuteMenu, false, false);

	return EErrorType::NONE;
}

void IntroMenu_Quit::OnTrigger_ExcuteMenu()
{
	GameCtx::I()->setCurrentGameState(EGameState::TERMINATION_SUCCESS);
	DEBUG_LOG("IntroMenu_Quit���� ���� ����!");
}
