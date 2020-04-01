// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 모든 정적 오브젝트의 기반입니다.
// =====================================================================================

#ifndef STATIC_OBJ__H__
#define STATIC_OBJ__H__

#include "GameObject.h"

class StaticObj : public GameObj
{
public:
#pragma region 생성자 및 소멸자
	using GameObj::GameObj;
	virtual ~StaticObj() = default;
#pragma endregion

	virtual EGameObjType getType() const override
	{
		return EGameObjType::STATIC;
	}

private:
	
};

#endif