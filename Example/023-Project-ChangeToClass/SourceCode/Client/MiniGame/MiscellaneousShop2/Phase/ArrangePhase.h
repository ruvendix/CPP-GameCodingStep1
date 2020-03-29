// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �������Դϴ�.
// ���� ��������� �κ��丮�� ������ �� �ֽ��ϴ�.
// =====================================================================================

#ifndef ARRANGE_PHASE_H__
#define ARRANGE_PHASE_H__

#include "PhaseBase.h"

class ArrangePhase : public PhaseBase
{
public:
#pragma region ������ �� �Ҹ���
	using PhaseBase::PhaseBase;
	virtual ~ArrangePhase() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnRender() override;
};

#endif