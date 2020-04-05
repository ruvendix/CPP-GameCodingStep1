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

#include "Element\Phase.h"

class ArrangePhase : public Phase
{
public:
#pragma region ������ �� �Ҹ���
	using Phase::Phase;
	virtual ~ArrangePhase() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnRender() override;
};

#endif