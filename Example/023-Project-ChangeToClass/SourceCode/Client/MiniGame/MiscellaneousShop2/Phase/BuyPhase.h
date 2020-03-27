// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �������Դϴ�.
// ���� ��������� ���� �������� ������ �� �ֽ��ϴ�.
// =====================================================================================

#ifndef BUY_PHASE_H__
#define BUY_PHASE_H__

#include "PhaseBase.h"
#include "..\Item\ItemDBEnum.h"

class ItemBase;

class BuyPhase : public PhaseBase
{
	FRIEND_WITH_HELPER(BuyPhaseHelper);
	INPUT_FPS_LIMITED(12);

public:
#pragma region ������ �� �Ҹ���
	using PhaseBase::PhaseBase;
	virtual ~BuyPhase() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnPostInitialize() override;
	virtual EErrorType OnInput() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;

private:
	EItemDBType m_itemDBType = EItemDBType::POTION;
	std::vector<ItemBase*> m_vecDisplayItem;
	bool m_bSelectedProductFamily = false;
};

#endif