// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ����ŷ�Դϴ�.
// =====================================================================================

#ifndef VIKING_H__
#define VIKING_H__

#include "Unit.h"

class Viking final : public Unit
{
	DECLARE_RTTI(Viking, Unit);

public:
#pragma region ������ �� �Ҹ���
	using Unit::Unit;
	virtual ~Viking() = default;
#pragma endregion
};

#endif