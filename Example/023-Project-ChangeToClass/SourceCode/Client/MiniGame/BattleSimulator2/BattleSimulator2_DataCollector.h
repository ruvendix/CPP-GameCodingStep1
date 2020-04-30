// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2���� ���Ǵ� ������ �����Դϴ�.
// ���� ������ �����Ϳ� ���ӿ��� �� �� ���˴ϴ�.
// =====================================================================================

#ifndef BATTLE_SIMULATOR2_DATA_COLLECTOR__H__
#define BATTLE_SIMULATOR2_DATA_COLLECTOR__H__

#include "Common\CommonNecessary.h"
#include "Common\CommonMacro.h"
#include "Common\CommonEnum.h"
#include "GameObject\ObjectID.h"

struct BattleData
{
	Int32 totalUnitCnt = 0;
	Int32 remainUnitCnt = 0;
	Int32 deathUnitCnt = 0;
	Int32 totalAttackDamage = 0;
};

enum class EBattleDataType : Int32
{
	TOTAL_UNIT_CNT = 0,
	REMAIN_UNIT_CNT,
	DEATH_UNIT_CNT,
	TOTAL_ATTACK_DAMAGE,
};

class Unit;
class Viking;
class MedievalKnight;
class StopwatchTimer;

using UnitPtr = std::shared_ptr<Unit>;
using VikingPtr = std::shared_ptr<Viking>;
using MedievalKnightPtr = std::shared_ptr<MedievalKnight>;
using StopwatchTimerPtr = std::shared_ptr<StopwatchTimer>;
using BattleDataPtr = std::shared_ptr<BattleData>;
using MapPrototypeUnit = MapCustom<EObjID, UnitPtr>;
using MapBattleData = MapCustom<EObjID, BattleDataPtr>;

class BattleSimulator2_DataCollector final
{
	DECLARE_PHOENIX_SINGLETON(BattleSimulator2_DataCollector);

public:
	void Initialize();
	void Finalize();

	UnitPtr FindPrototypeUnit(EObjID ID) const;
	
	void StartBattleTime();
	void EndBattleTime();
	void ModifyBattleData(EObjID unitID, EBattleDataType dataType, Int32 data);
	void ModifyBattleData(EObjID unitID, EBattleDataType dataType, EDataProgressDir dir, Int32 data);

	Int32 FindBattleData(EObjID unitID, EBattleDataType dataType) const;
	bool IsBattleEnd() const;

	TSize getPrototypeUnitCnt() const
	{
		return m_mapPrototypeUnit.Size();
	}

	StopwatchTimerPtr getBattleTimer() const
	{
		return m_spBattleTimer;
	}

private:
	BattleData m_vikingBattleData;
	BattleData m_medievalKnightBattleData;
	StopwatchTimerPtr m_spBattleTimer;

	MapBattleData m_mapBattleData;
	MapPrototypeUnit m_mapPrototypeUnit;
};

#endif