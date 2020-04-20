// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// �߼�����Դϴ�.
// =====================================================================================

#ifndef MEDIEVAL_KNIGHT_H__
#define MEDIEVAL_KNIGHT_H__

#include "Unit.h"

class MedievalKnight;
using MedievalKnightPtr = std::shared_ptr<MedievalKnight>;

class MedievalKnight final : public Unit
{
	DECLARE_RTTI(MedievalKnight, Unit);

public:
#pragma region ������ �� �Ҹ���
	using Unit::Unit;
	virtual ~MedievalKnight() = default;
#pragma endregion

	MedievalKnightPtr Clone();
};

#endif