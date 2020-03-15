// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 기본 유닛입니다.
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
