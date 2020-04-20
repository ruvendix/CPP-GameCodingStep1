// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2���� ���Ǵ� ������ �����Դϴ�.
// ���� ������ �����Ϳ� ���ӿ��� �� �� ���˴ϴ�.
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
#pragma region ����ŷ �ʱ�ȭ �� ���
	VikingPtr spViking = std::make_shared<Viking>("Viking", EDynamicObjID::VIKING, "��");

	spViking->setRange(12);
	spViking->setHP(1980);
	spViking->setMaxHP(1980);
	spViking->setMoveSpeed(1.6f);
	spViking->setAttackDamage(18);
	spViking->setAttackSuccessRate(0.58f);

	m_mapPrototypeUnit.Subscribe(EDynamicObjID::VIKING, spViking);
#pragma endregion

#pragma region �߼���� �ʱ�ȭ �� ���
	MedievalKnightPtr spMedievalKnight = std::make_shared<MedievalKnight>("MedievalKnight", EDynamicObjID::MEDIEVAL_KNIGHT, "��");

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

		// ���� ����� ���� ���� �ϳ��� 0�̸� ��Ʋ ����!
		if (remainUnitCnt == 0)
		{
			return true;
		}
	}

	return false;
}
