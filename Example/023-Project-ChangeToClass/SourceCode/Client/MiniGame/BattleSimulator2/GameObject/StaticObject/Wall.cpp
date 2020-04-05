// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터의 월드에 사용되는 벽입니다.
// =====================================================================================

#include "PCH.h"
#include "Wall.h"

#include "Controller\ConsoleController.h"

EErrorType Wall::OnRender()
{
	const COORD& pos = getPos();
	PUT_STRING(pos.X * getShape().size(), pos.Y, getShape().c_str());
	return EErrorType::NONE;
}
