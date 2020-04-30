// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2에서 사용되는 데이터 모음입니다.
// 레벨 디자인 에디터와 게임에서 둘 다 사용됩니다.
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