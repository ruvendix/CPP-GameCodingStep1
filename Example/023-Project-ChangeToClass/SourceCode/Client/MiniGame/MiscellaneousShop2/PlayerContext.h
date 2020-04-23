// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �÷��̾��� ���� �����Դϴ�.
// ������ �κ��丮�� �����ݸ� �ֽ��ϴ�.
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