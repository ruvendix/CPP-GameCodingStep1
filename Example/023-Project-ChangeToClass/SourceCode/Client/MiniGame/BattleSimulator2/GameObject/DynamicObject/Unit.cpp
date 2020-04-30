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

Unit::Unit(const Unit& src)
{
	Copy(src);
}

Unit::Unit(const std::string_view& szName, EObjID objID, const std::string_view& szShape) :
	DynamicObj(szName)
{
	setID(objID);
	setShape(szShape);
}

EErrorType Unit::OnSaveFile(FILE* pFileStream)
{
	if (DynamicObj::OnSaveFile(pFileStream) == EErrorType::SAVE_FILE_FAIL)
	{
		return EErrorType::SAVE_FILE_FAIL;
	}

	fwrite(&m_HP, sizeof(m_HP), 1, pFileStream);
	fwrite(&m_maxHP, sizeof(m_maxHP), 1, pFileStream);
	fwrite(&m_range, sizeof(m_range), 1, pFileStream);
	fwrite(&m_attackDamage, sizeof(m_attackDamage), 1, pFileStream);
	fwrite(&m_attackSuccessRate, sizeof(m_attackSuccessRate), 1, pFileStream);

	return EErrorType::NOTHING;
}

EErrorType Unit::OnLoadFile(FILE* pFileStream)
{
	if (DynamicObj::OnLoadFile(pFileStream) == EErrorType::LOAD_FILE_FAIL)
	{
		return EErrorType::LOAD_FILE_FAIL;
	}

	fread(&m_HP, sizeof(m_HP), 1, pFileStream);
	fread(&m_maxHP, sizeof(m_maxHP), 1, pFileStream);
	fread(&m_range, sizeof(m_range), 1, pFileStream);
	fread(&m_attackDamage, sizeof(m_attackDamage), 1, pFileStream);
	fread(&m_attackSuccessRate, sizeof(m_attackSuccessRate), 1, pFileStream);

	return EErrorType::NOTHING;
}

EErrorType Unit::OnFinalize()
{
	ClearUnitInRange();
	return EErrorType::NOTHING;
}

void Unit::Attack(UnitPtr spTargetUnit)
{
	CHECK_NULLPTR_RETURN_VOID(spTargetUnit);

	if (m_attackSuccessRate > rx_math::Random::GenerateRandom(0.0f, 1.0f))
	{
		spTargetUnit->Damage(m_attackDamage);
	}
}

void Unit::Damage(Int32 damage)
{
	m_HP -= damage;
}

void Unit::FilterUnitInRange(const std::vector<UnitPtr>& vecUnit, const SizeInfo& worldSize)
{
	COORD rangeStartPos
	{
		static_cast<SHORT>(getPos().X - getRange()),
		static_cast<SHORT>(getPos().Y - getRange()),
	};

	COORD rangeEndPos
	{
		static_cast<SHORT>(getPos().X + getRange()),
		static_cast<SHORT>(getPos().Y + getRange()),
	};

	for (auto& iter : vecUnit)
	{
		CHECK_NULLPTR_CONTINUE(iter);

		if (rx_math::IsSamePos(getPos(), iter->getPos()))
		{
			//DEBUG_LOG("�� �н�!");
			continue;
		}

		// �þ߿� ���� ������ ����Ʈ�� �߰�!
		// �װų� ���� ���� ���ֵ� ����!
		if (rx_math::IsPointInRect(iter->getPos(), rangeStartPos, rangeEndPos))
		{
			m_listUnitInRange.push_back(iter);
		}
	}
}

void Unit::ClearUnitInRange()
{
	m_listUnitInRange.clear();
}

void Unit::AdjustMoveAxisDir(UnitPtr spUnit)
{
	const COORD& targetPos = spUnit->getPos();

	if (getPos().X < targetPos.X)
	{
		setMoveAxisDir(0, EDataProgressDir::POSITIVENESS);
	}
	else if (getPos().X > targetPos.X)
	{
		setMoveAxisDir(0, EDataProgressDir::NEGATIVENESS);
	}

	if (getPos().Y < targetPos.Y)
	{
		setMoveAxisDir(1, EDataProgressDir::POSITIVENESS);
	}
	else if (getPos().Y > targetPos.Y)
	{
		setMoveAxisDir(1, EDataProgressDir::NEGATIVENESS);
	}
}

void Unit::ChangeLockOnTargetUnit(UnitPtr spTarget)
{
	if (spTarget == nullptr)
	{
		m_spLockOnTargetUnit = nullptr;
		return;
	}

	if ( (spTarget->IsSameState(EUnitState::DEATH)) ||
		 (spTarget->IsSameState(EUnitState::ERASE)) )
	{
		m_spLockOnTargetUnit = nullptr;
		return;
	}
	
	m_spLockOnTargetUnit = spTarget;
}

EErrorType Unit::Copy(const Unit& src)
{
	if (DynamicObj::Copy(src) == EErrorType::COPY_FAIL)
	{
		return EErrorType::COPY_FAIL;
	}

	m_spLockOnTargetUnit = nullptr;
	ClearUnitInRange();

	setHP(src.getHP());
	setMaxHP(src.getMaxHP());
	setRange(src.getRange());
	setAttackDamage(src.getAttackDamage());
	setAttackSuccessRate(src.getAttackSuccessRate());

	return EErrorType::NOTHING;
}

UnitPtr Unit::Clone()
{
	return std::make_shared<Unit>(*this);
}

UnitPtr Unit::SearchShortestPathEnemyInRange(_Out_ SizeInfo& distance) const
{
	UnitPtr spEnemyUnit = nullptr;
	Uint32 absSum = UINT_MAX;

	for (const auto& iter : m_listUnitInRange)
	{
		CHECK_NULLPTR_CONTINUE(iter);
		
		if (getID() == iter->getID())
		{
			continue;
		}

		// ��ǥ ����
		const COORD& pos = getPos();
		const COORD& targetPos = iter->getPos();

		// ���� ���� ���� ���� ���� ���� �� �ִܰŸ�
		distance.width = std::abs(pos.X - targetPos.X);
		distance.height = std::abs(pos.Y - targetPos.Y);

		Uint32 retAbsSum = distance.width + distance.height;
		if (retAbsSum < absSum)
		{
			spEnemyUnit = iter;
			absSum = retAbsSum;
		}
	}

	if (spEnemyUnit == nullptr)
	{
		return nullptr;
	}

	// ��ǥ ����
	const COORD& pos = getPos();
	const COORD& targetPos = spEnemyUnit->getPos();

	// ������ ���ְ��� �Ÿ��� �ٽ� ���!
	distance.width = std::abs(pos.X - targetPos.X);
	distance.height = std::abs(pos.Y - targetPos.Y);

	//DEBUG_LOG("���� ª�� �Ÿ� (%d, %d)", spUnit->getPos().X, spUnit->getPos().Y);
	return spEnemyUnit;
}