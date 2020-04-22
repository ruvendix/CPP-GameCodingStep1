// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2�� ���� ����� �����մϴ�.
// ������ �����͸� �̿��ؼ� ������ ����ϰ� �̱� ���� �˷��ݴϴ�.
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