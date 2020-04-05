// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2에서 사용되는 기본 동적 오브젝트입니다.
// =====================================================================================

#ifndef DYNAMIC_OBJ_BATTLE_SIMULATOR2__H__
#define DYNAMIC_OBJ_BATTLE_SIMULATOR2__H__

#include "Element\GameObject\DynamicObject.h"
#include "DynamicObjectID.h"

class DynamicObj_BattleSimulator2 : public DynamicObj
{
public:
#pragma region 생성자 및 소멸자
	using DynamicObj::DynamicObj;

	DynamicObj_BattleSimulator2() = default;
	virtual ~DynamicObj_BattleSimulator2() = default;

	DynamicObj_BattleSimulator2(EDynamicObjID dynamicObjID);
#pragma endregion

	EDynamicObjID getStaticObjID() const
	{
		return m_dynamicObjID;
	}

private:
	EDynamicObjID m_dynamicObjID = EDynamicObjID::UNKNOWN;
};

#endif