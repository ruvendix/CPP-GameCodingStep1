// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �������Դϴ�.
// ���� ��������� �ٸ� ����� ������ �� �ֽ��ϴ�.
// =====================================================================================

#ifndef ENTRANCE_PHASE_H__
#define ENTRANCE_PHASE_H__

#include "PhaseBase.h"

class EntrancePhase : public PhaseBase
{
public:
#pragma region ������ �� �Ҹ���
	using PhaseBase::PhaseBase;
	virtual ~EntrancePhase() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;
};

#endif