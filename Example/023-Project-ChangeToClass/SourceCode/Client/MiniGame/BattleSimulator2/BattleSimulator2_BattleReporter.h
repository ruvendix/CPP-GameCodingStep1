// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2의 게임 결과를 보고합니다.
// 수집한 데이터를 이용해서 점수를 계산하고 이긴 팀을 알려줍니다.
// =====================================================================================

#ifndef BATTLE_SIMULATOR2_BATTLE_REPORTER__H__
#define BATTLE_SIMULATOR2_BATTLE_REPORTER__H__

#include "Common\CommonNecessary.h"
#include "Common\CommonMacro.h"
#include "Common\CommonEnum.h"

using ArrTotalScore = std::array<Int32, 2>;

class BattleSimulator2_BattleReporter final
{
	DECLARE_PHOENIX_SINGLETON(BattleSimulator2_BattleReporter);

public:
	void Result();
	void DrawUnitStat() const;
	void DrawRemainUnit() const;
	void DrawReport() const;

private:
	Int32 m_elapsedBattleTimeSecond = 0;

	std::string m_strBattleStartTime;
	std::string m_strBattleEndTime;
	std::string m_strWinnerGuide;

	ArrTotalScore m_arrTotalScore;
};

#endif