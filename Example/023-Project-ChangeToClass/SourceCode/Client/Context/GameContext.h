// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���ӿ��� ���������� ���Ǵ� ���� �����Դϴ�.
// ���Ӹ��� �ٸ� ������ ������ �� �ֽ��ϴ�.
// =====================================================================================

#ifndef GAME_CONTEXT__H__
#define GAME_CONTEXT__H__

#include "Common\CommonStruct.h"
#include "Common\CommonMacro.h"

class GameCtx final
{
	DECLARE_SINGLETON(GameCtx);

public:
	bool IsTerminateGame() const
	{
		if ( (m_currentGameState == EGameState::TERMINATION_SUCCESS) ||
			 (m_currentGameState == EGameState::TERMINATION_ABNORMALITY) )
		{
			return true;
		}

		return false;
	}

	EGameState getCurrentGameState() const
	{
		return m_currentGameState;
	}

	void setCurrentGameState(EGameState nextGameState)
	{
		m_currentGameState = nextGameState;
	}

private:
	EGameState m_currentGameState = EGameState::NONE;
};

#endif