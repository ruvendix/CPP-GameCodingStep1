// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2의 월드에 사용되는 벽입니다.
// =====================================================================================

#ifndef WALL__H__
#define WALL__H__

#include "StaticObject_BattleSimulator2.h"

class Wall : public StaticObj_BattleSimulator2
{
public:
#pragma region 생성자 및 소멸자
	using StaticObj_BattleSimulator2::StaticObj_BattleSimulator2;
	virtual ~Wall() = default;
#pragma endregion

	virtual EErrorType OnRender() override;
};

#endif