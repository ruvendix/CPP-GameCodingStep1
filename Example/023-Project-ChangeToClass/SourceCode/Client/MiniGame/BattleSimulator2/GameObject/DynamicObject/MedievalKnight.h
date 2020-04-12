// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 중세기사입니다.
// =====================================================================================

#ifndef MEDIEVAL_KNIGHT_H__
#define MEDIEVAL_KNIGHT_H__

#include "Unit.h"

class MedievalKnight final : public Unit
{
	DECLARE_RTTI(MedievalKnight, Unit);

public:
#pragma region 생성자 및 소멸자
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