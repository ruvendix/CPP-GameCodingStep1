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

class MedievalKnight final : public Unit
{
	DECLARE_RTTI(MedievalKnight, Unit);

public:
#pragma region ������ �� �Ҹ���
	using Unit::Unit;
	virtual ~MedievalKnight() = default;
#pragma endregion

	static Int32 GetTotalCnt()
	{
		return m_totalCnt;
	}

	static void SetTotalCnt(Int32 totalCnt)
	{
		m_totalCnt = totalCnt;
	}

private:
	static Int32 m_totalCnt;
};

#endif