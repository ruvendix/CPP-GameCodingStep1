// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 게임에서 전역적으로 사용되는 정보 모음입니다.
// 게임마다 다른 정보로 구성될 수 있습니다.
// =====================================================================================

#ifndef GAME_CONTEXT__H__
#define GAME_CONTEXT__H__

#include "Common\CommonStruct.h"
#include "Common\CommonMacro.h"

enum class EGameState : Int32
{
	NONE = 0,
	INIT,
	UPDATE,
	RENDER,
	FINAL,
	TERMINATION_SUCCESS,
	TERMINATION_ABNORMALITY,
};

class GameCtx final
{
	DECLARE_PHOENIX_SINGLETON(GameCtx);

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