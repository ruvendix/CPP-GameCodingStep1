// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �پ��� �������� ���� �� �Ǹ��ϴ� ��ȭ����2�Դϴ�.
// =====================================================================================

#ifndef MISCELLANEOUS_SHOP2_H__
#define MISCELLANEOUS_SHOP2_H__

#include "Element\GameElement.h"

class PhaseBase;

class MiscellanouseShop2 final : public GameElem
{
	FRIEND_WITH_HELPER(MiscellaneousShop2Helper);

public:
#pragma region ������ �� �Ҹ���
	using GameElem::GameElem;
	virtual ~MiscellanouseShop2() = default;
#pragma endregion

	virtual EErrorType OnInitialize() override;
	virtual EErrorType OnUpdate() override;
	virtual EErrorType OnRender() override;
	virtual EErrorType OnFinalize() override;

private:
	PhaseBase* m_pCurrentPhase = nullptr;
};

#endif