// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 바이킹입니다.
// =====================================================================================

#ifndef VIKING_H__
#define VIKING_H__

#include "Unit.h"

class Viking final : public Unit
{
	DECLARE_RTTI(Viking, Unit);

public:
#pragma region 생성자 및 소멸자
	using Unit::Unit;
	virtual ~Viking() = default;
#pragma endregion
};

#endif