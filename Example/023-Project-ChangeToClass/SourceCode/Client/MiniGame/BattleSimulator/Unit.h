// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 기본 유닛입니다.
// =====================================================================================

#ifndef UNIT_H__
#define UNIT_H__

#include "Common\CommonType.h"

class Unit
{
public:
#pragma region 생성자 및 소멸자
	Unit() = default;
	virtual ~Unit() = default;
#pragma endregion

	void Attack(std::shared_ptr<Unit> spTargetUnit);
	void Damage(Int32 damageVal);

	bool IsDeath() const
	{
		return (m_HP < 0);
	}

#pragma region 접근자 Getter
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
#pragma endregion

#pragma region 접근자 Setter
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
#pragma endregion

private:
	Int32  m_HP = 0;
	Int32  m_maxHP = 0;
	Int32  m_attackDamage = 0;
	Real32 m_attackSuccessRate = 0.0f;
};

#endif