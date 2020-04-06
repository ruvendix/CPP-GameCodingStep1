// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 배틀 시뮬레이터2에서 사용되는 기본 동적 오브젝트입니다.
// =====================================================================================

#ifndef BATTLE_SIMULATOR2_DYNAMIC_OBJ__H__
#define BATTLE_SIMULATOR2_DYNAMIC_OBJ__H__

#include "Element\GameObject\DynamicObject.h"
#include "DynamicObjectID.h"

class BattleSimulator2_DynamicObj : public DynamicObj
{
public:
#pragma region 생성자 및 소멸자
	using DynamicObj::DynamicObj;

	BattleSimulator2_DynamicObj() = default;
	virtual ~BattleSimulator2_DynamicObj() = default;

	BattleSimulator2_DynamicObj(EDynamicObjID objID);
#pragma endregion

	virtual EErrorType OnPreSaveFile(FILE* pFileStream) override;

	EDynamicObjID getObjID() const
	{
		return m_objID;
	}

	void setObjID(EDynamicObjID objID)
	{
		m_objID = objID;
	}

private:
	EDynamicObjID m_objID = EDynamicObjID::UNKNOWN;
};

#endif