// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �⺻ �����Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "Unit.h"

#include "Math\Random.h"

Unit::Unit(EDynamicObjID objID, const std::string_view& szShape)
{
	setObjID(objID);
	setShape(szShape);
}

void Unit::Attack(std::shared_ptr<Unit> spTargetUnit)
{
	if (m_attackSuccessRate > math::RandomUtil::GenerateUniformDistribution(0.0f, 1.0f))
	{
		spTargetUnit->Damage(m_attackDamage);
	}
}

void Unit::Damage(Int32 damage)
{
	m_HP -= damage;
}

void Unit::Copy(std::shared_ptr<Unit> spUnit)
{
	setObjID(spUnit->getObjID());
	setShape(spUnit->getShape());
	setPos(spUnit->getPos());
}