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

void Unit::Attack(Unit* pTargetUnit)
{
	CHECK_NULLPTR_RETURN_VOID(pTargetUnit);

	if (m_attackSuccessRate > math::RandomUtil::GenerateUniformDistribution(0.0f, 1.0f))
	{
		pTargetUnit->Damage(m_attackDamage);
	}
}

void Unit::Damage(Int32 damageVal)
{
	m_HP -= damageVal;
}
