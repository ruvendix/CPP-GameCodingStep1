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

Unit::Unit(const std::string_view& szName, EDynamicObjID objID, const std::string_view& szShape) :
	DynamicObj(szName)
{
	setID(common_func::ToUnderlyingType(objID));
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
	m_listUnitInRange.clear();
	return EErrorType::NOTHING;
}

void Unit::Attack(UnitPtr spTargetUnit)
{
	if (m_attackSuccessRate > math::RandomUtil::GenerateRandom(0.0f, 1.0f))
	{
		spTargetUnit->Damage(m_attackDamage);
	}
}

void Unit::Damage(Int32 damage)
{
	m_HP -= damage;
}

void Unit::Copy(UnitPtr spUnit)
{
	setID(spUnit->getID());
	setShape(spUnit->getShape());
	setPos(spUnit->getPos());
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

		if (math::IsSamePos(getPos(), iter->getPos()))
		{
			//DEBUG_LOG("난 패스!");
			continue;
		}

		if (iter->IsDeath())
		{
			continue;
		}

		// 시야에 들어온 유닛은 리스트에 추가!
		if (math::IsPointInRect(iter->getPos(), rangeStartPos, rangeEndPos))
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
		setMoveAxisDir(0, EMoveAxisDir::POSITIVENESS);
	}
	else if (getPos().X > targetPos.X)
	{
		setMoveAxisDir(0, EMoveAxisDir::NEGATIVENESS);
	}

	if (getPos().Y < targetPos.Y)
	{
		setMoveAxisDir(1, EMoveAxisDir::POSITIVENESS);
	}
	else if (getPos().Y > targetPos.Y)
	{
		setMoveAxisDir(1, EMoveAxisDir::NEGATIVENESS);
	}
}

Unit::UnitPtr Unit::SearchShortestPathEnemyInRange() const
{
	UnitPtr spUnit = nullptr;
	Uint32 absSum = UINT_MAX;

	for (const auto& iter : m_listUnitInRange)
	{
		CHECK_NULLPTR_CONTINUE(iter);
		
		if (getID() == iter->getID())
		{
			continue;
		}
		
		// 나와 절댓값 차의 합이 가장 작은 게 최단거리
		const COORD& targetPos = iter->getPos();
		Uint32 intervalX = std::abs(getPos().X - targetPos.X);
		Uint32 intervalY = std::abs(getPos().Y - targetPos.Y);

		Uint32 retAbsSum = intervalX + intervalY;
		if (retAbsSum < absSum)
		{
			spUnit = iter;
			absSum = retAbsSum;
		}
	}

	//DEBUG_LOG("가장 짧은 거리 (%d, %d)", spUnit->getPos().X, spUnit->getPos().Y);
	return spUnit;
}
