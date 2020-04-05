// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2에서 사용되는 기본 정적 오브젝트입니다.
// =====================================================================================

#ifndef STATIC_OBJ_BATTLE_SIMULATOR2__H__
#define STATIC_OBJ_BATTLE_SIMULATOR2__H__

#include "Element\GameObject\StaticObject.h"
#include "StaticObjectID.h"

class StaticObj_BattleSimulator2 : public StaticObj
{
public:
#pragma region 생성자 및 소멸자
	using StaticObj::StaticObj;

	StaticObj_BattleSimulator2() = default;
	virtual ~StaticObj_BattleSimulator2() = default;

	StaticObj_BattleSimulator2(EStaticObjID staticObjID);
#pragma endregion

	virtual EErrorType OnPreSaveFile(FILE* pFileStream) override;

	EStaticObjID getStaticObjID() const
	{
		return m_staticObjID;
	}

private:
	EStaticObjID m_staticObjID = EStaticObjID::UNKNOWN;
};

#endif