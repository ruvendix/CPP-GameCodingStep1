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

#include "Context\GameContext.h"

EErrorType IntroMenu_Quit::OnExcute()
{
	DEBUG_LOG("IntroMenu_Quit���� ���� ����!");
	GameCtx::I()->setCurrentGameState(EGameState::TERMINATION_SUCCESS);
	return EErrorType::NONE;
}