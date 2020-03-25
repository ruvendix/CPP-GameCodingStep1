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
	FRAME_UPDATE_LIMITED(3);

public:
#pragma region ������ �� �Ҹ���
	using PhaseBase::PhaseBase;
	virtual ~SellPhase() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;
};

#endif