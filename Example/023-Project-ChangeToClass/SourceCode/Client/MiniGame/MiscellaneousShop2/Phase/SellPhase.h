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

#include "PhaseBase.h"

class SellPhase : public PhaseBase
{
	FRIEND_WITH_HELPER(SellPhaseHelper);
	INPUT_FPS_LIMITED(12);

public:
#pragma region ������ �� �Ҹ���
	using PhaseBase::PhaseBase;
	virtual ~SellPhase() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;
};

#endif