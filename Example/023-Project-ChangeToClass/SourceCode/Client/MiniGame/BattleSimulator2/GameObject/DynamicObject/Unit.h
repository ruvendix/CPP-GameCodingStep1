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

#include "Common\CommonType.h"
#include "Element\GameObject\DynamicObject.h"
#include "..\ObjectID.h"
#include "..\ObjectState.h"

class Unit : public DynamicObj
{
	DECLARE_RTTI(Unit, DynamicObj);

public:
	using UnitPtr = std::shared_ptr<Unit>;

#pragma region ������ �� �Ҹ���
	using DynamicObj::DynamicObj;

	Unit() = default;
	virtual ~Unit() = default;
	
	Unit(const std::string_view& szName, EDynamicObjID objID, const std::string_view& szShape);
#pragma endregion

	virtual EErrorType OnSaveFile(FILE* pFileStream) override;
	virtual EErrorType OnLoadFile(FILE* pFileStream) override;
	virtual EErrorType OnFinalize() override;

	void Attack(UnitPtr spTargetUnit);
	void Damage(Int32 damage);
	void Copy(UnitPtr spUnit);
	
	void FilterUnitInRange(const std::vector<UnitPtr>& vecUnit, const SizeInfo& worldSize);
	void ClearUnitInRange();
	void AdjustMoveAxisDir(UnitPtr spUnit);

	UnitPtr SearchShortestPathEnemyInRange() const;

	bool IsDeath() const
	{
		return (m_HP <= 0);
	}

#pragma region ������ Getter
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

	EUnitState getState() const
	{
		return m_state;
	}

	Int32 getRange() const
	{
		return m_range;
	}
#pragma endregion

#pragma region ������ Setter
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

	void setState(EUnitState state)
	{
		m_state = state;
	}

	void setRange(Int32 range)
	{
		m_range = range;
	}
#pragma endregion

private:
	Int32  m_HP = 0;
	Int32  m_maxHP = 0;
	Int32  m_range = 0;
	Int32  m_attackDamage = 0;
	Real32 m_attackSuccessRate = 0.0f;
	EUnitState m_state = EUnitState::IDLE;
	std::list<UnitPtr> m_listUnitInRange; // �þ� ���� �ȿ� ���� ���ֵ� (�ڱ� �ڽ� ����)
};

#endif