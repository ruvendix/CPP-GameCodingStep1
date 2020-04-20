// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2에서 사용되는 데이터 모음입니다.
// 레벨 디자인 에디터와 게임에서 둘 다 사용됩니다.
// =====================================================================================

#include "PCH.h"
#include "BattleSimulator2_DataCollector.h"

#include "GameObject\DynamicObject\Viking.h"
#include "GameObject\DynamicObject\MedievalKnight.h"

namespace
{
	void ModfityBattleDataImpl(EDataProgressDir dir, Int32 data, _Out_ Int32& targetData)
	{
		if (dir == EDataProgressDir::POSITIVENESS)
		{
			targetData += data;
		}
		else if (dir == EDataProgressDir::NEGATIVENESS)
		{
			targetData -= data;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

DEFINE_PHOENIX_SINGLETON(BattleSimulator2_DataCollector);

void BattleSimulator2_DataCollector::Initialize()
{
#pragma region 바이킹 초기화 및 등록
	VikingPtr spViking = std::make_shared<Viking>("Viking", EDynamicObjID::VIKING, "♠");

	spViking->setRange(12);
	spViking->setHP(1980);
	spViking->setMaxHP(1980);
	spViking->setMoveSpeed(1.6f);
	spViking->setAttackDamage(18);
	spViking->setAttackSuccessRate(0.58f);

	m_mapPrototypeUnit.Subscribe(EDynamicObjID::VIKING, spViking);
#pragma endregion

#pragma region 중세기사 초기화 및 등록
	MedievalKnightPtr spMedievalKnight = std::make_shared<MedievalKnight>("MedievalKnight", EDynamicObjID::MEDIEVAL_KNIGHT, "Ω");

	spMedievalKnight->setRange(12);
	spMedievalKnight->setHP(1800);
	spMedievalKnight->setMaxHP(1800);
	spMedievalKnight->setMoveSpeed(1.2f);
	spMedievalKnight->setAttackDamage(14);
	spMedievalKnight->setAttackSuccessRate(0.78f);

	m_mapPrototypeUnit.Subscribe(EDynamicObjID::MEDIEVAL_KNIGHT, spMedievalKnight);
#pragma endregion

	m_mapBattleData.Subscribe(EDynamicObjID::VIKING, std::make_shared<BattleData>());
	m_mapBattleData.Subscribe(EDynamicObjID::MEDIEVAL_KNIGHT, std::make_shared<BattleData>());
}

void BattleSimulator2_DataCollector::Finalize()
{
	m_mapBattleData.Clear();
	m_mapPrototypeUnit.Clear();
}

UnitPtr BattleSimulator2_DataCollector::FindPrototypeUnit(EDynamicObjID ID) const
{
	return m_mapPrototypeUnit.Find(ID);
}

void BattleSimulator2_DataCollector::ModifyBattleData(EDynamicObjID unitID, EBattleDataType dataType, Int32 data)
{
	BattleDataPtr spBattleData = m_mapBattleData.Find(unitID);

	switch (dataType)
	{
	case EBattleDataType::TOTAL_UNIT_CNT:
	{
		spBattleData->totalUnitCnt = data;
		break;
	}

	case EBattleDataType::REMAIN_UNIT_CNT:
	{
		spBattleData->remainUnitCnt = data;
		break;
	}

	case EBattleDataType::DEATH_UNIT_CNT:
	{
		spBattleData->deathUnitCnt = data;
		break;
	}

	case EBattleDataType::TOTAL_ATTACK_DAMAGE:
	{
		spBattleData->totalAttackDamage = data;
		break;
	}

	default:
	{
		break;
	}
	}
}

void BattleSimulator2_DataCollector::ModifyBattleData(EDynamicObjID unitID,
	EBattleDataType dataType, EDataProgressDir dir, Int32 data)
{
	BattleDataPtr spBattleData = m_mapBattleData.Find(unitID);

	switch (dataType)
	{
	case EBattleDataType::TOTAL_UNIT_CNT:
	{
		ModfityBattleDataImpl(dir, data, spBattleData->totalUnitCnt);
		break;
	}

	case EBattleDataType::REMAIN_UNIT_CNT:
	{
		ModfityBattleDataImpl(dir, data, spBattleData->remainUnitCnt);
		break;
	}

	case EBattleDataType::DEATH_UNIT_CNT:
	{
		ModfityBattleDataImpl(dir, data, spBattleData->deathUnitCnt);
		break;
	}

	case EBattleDataType::TOTAL_ATTACK_DAMAGE:
	{
		ModfityBattleDataImpl(dir, data, spBattleData->totalAttackDamage);
		break;
	}

	default:
	{
		break;
	}
	}
}

Int32 BattleSimulator2_DataCollector::FindBattleData(EDynamicObjID unitID, EBattleDataType dataType) const
{
	BattleDataPtr spBattleData = m_mapBattleData.Find(unitID);

	switch (dataType)
	{
	case EBattleDataType::TOTAL_UNIT_CNT:
	{
		return spBattleData->totalUnitCnt;
	}

	case EBattleDataType::REMAIN_UNIT_CNT:
	{
		return spBattleData->remainUnitCnt;
	}

	case EBattleDataType::DEATH_UNIT_CNT:
	{
		return spBattleData->deathUnitCnt;
	}

	case EBattleDataType::TOTAL_ATTACK_DAMAGE:
	{
		return spBattleData->totalAttackDamage;
	}

	default:
	{
		break;
	}
	}

	return 0;
}

bool BattleSimulator2_DataCollector::IsBattleEnd() const
{
	Int32 startID = common_func::ToUnderlyingType(EDynamicObjID::UNKNOWN) + 1;
	Int32 endID = common_func::ToUnderlyingType(EDynamicObjID::END);
	for (Int32 i = startID; i < endID; ++i)
	{
		Int32 remainUnitCnt = BattleSimulator2_DataCollector::I()->FindBattleData(
			static_cast<EDynamicObjID>(i), EBattleDataType::REMAIN_UNIT_CNT);

		// 유닛 목록중 남은 수가 하나라도 0이면 배틀 종료!
		if (remainUnitCnt == 0)
		{
			return true;
		}
	}

	return false;
}
