// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �⺻ �����Դϴ�.
// =====================================================================================

#ifndef UNIT_H__
#define UNIT_H__

#include "Element\GameElement.h"

class Unit
{
public:
#pragma region ������ �� �Ҹ���
	Unit() = default;
	virtual ~Unit() = default;
#pragma endregion

	void Attack(Unit* pTargetUnit);
	void Damage(Int32 damageVal);

	bool IsDeath() const
	{
		return (m_HP < 0);
	}

	Int32 getHP() const
	{
		return m_HP;
	}

	Int32 getMaxHP() const
	{
		return m_maxHP;
	}

	Int32 getAttackDamage() const
	{
		return m_attackDamage;
	}

	Real32 getAttackSuccessRate() const
	{
		return m_attackSuccessRate;
	}

	void setHP(Int32 HP)
	{
		m_HP = HP;
	}

	void setMaxHP(Int32 MaxHP)
	{
		m_maxHP = MaxHP;
	}

	void setAttackDamage(Int32 attackDamage)
	{
		m_attackDamage = attackDamage;
	}

	void setAttackSuccessRate(Real32 attackSuccessRate)
	{
		m_attackSuccessRate = attackSuccessRate;
	}

private:
	Int32  m_HP = 0;
	Int32  m_maxHP = 0;
	Int32  m_attackDamage = 0;
	Real32 m_attackSuccessRate = 0.0f;
};
#endif