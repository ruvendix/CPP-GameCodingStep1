// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �Ǹ� �������Դϴ�.
// �Ǹ� ��������� �������� �Ǹ��� �� �ֽ��ϴ�.
// =====================================================================================

#ifndef SELL_PHASE_H__
#define SELL_PHASE_H__

#include "Element\Phase.h"

class SellPhase : public Phase
{
	FRIEND_WITH_HELPER(SellPhaseHelper);
	INPUT_FPS_LIMITED(8);

public:
#pragma region ������ �� �Ҹ���
	using Phase::Phase;
	virtual ~SellPhase() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnRender() override;
};

#endif