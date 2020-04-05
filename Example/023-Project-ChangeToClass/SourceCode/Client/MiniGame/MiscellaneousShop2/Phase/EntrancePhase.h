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

#include "Element\Phase.h"
#include "Element\Menu\MenuTable_Matrix.h"

class EntrancePhase : public Phase
{
	FRIEND_WITH_HELPER(EntrancePhaseHelper);

public:
#pragma region ������ �� �Ҹ���
	using Phase::Phase;
	virtual ~EntrancePhase() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnRender() override;

private:
	std::shared_ptr<MenuTable_Mat> m_spMenuTable;
};

#endif