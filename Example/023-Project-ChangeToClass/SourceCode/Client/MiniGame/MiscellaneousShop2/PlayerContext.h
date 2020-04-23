// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 플레이어의 정보 모음입니다.
// 지금은 인벤토리와 소지금만 있습니다.
// =====================================================================================

#ifndef PLAYER_CONTEXT_H__
#define PLAYER_CONTEXT_H__

#include "Common\CommonType.h"
#include "Common\CommonMacro.h"
#include "Common\CommonNecessary.h"

class Inven;
using InvenPtr = std::shared_ptr<Inven>;

class PlayerCtx final
{
	DECLARE_PHOENIX_SINGLETON(PlayerCtx);

	static const Int32 MAX_GAME_MONEY = 9999;

public:
	void Initialize();

	void AddGameMoney(Int32 gameMoney)
	{
		m_gameMoney += gameMoney;
		rx_math::Clamp(m_gameMoney, 0, MAX_GAME_MONEY);
	}

	InvenPtr getInven() const
	{
		return m_spInven;
	}

	Int32 getGameMoney() const
	{
		return m_gameMoney;
	}

	void setGameMoney(Int32 gameMoney)
	{
		m_gameMoney = gameMoney;
	}

private:
	Int32 m_gameMoney = 0;
	InvenPtr m_spInven;
};

#endif