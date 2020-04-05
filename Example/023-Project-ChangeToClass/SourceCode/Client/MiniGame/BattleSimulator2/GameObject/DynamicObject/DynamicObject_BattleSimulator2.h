// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2���� ���Ǵ� �⺻ ���� ������Ʈ�Դϴ�.
// =====================================================================================

#ifndef DYNAMIC_OBJ_BATTLE_SIMULATOR2__H__
#define DYNAMIC_OBJ_BATTLE_SIMULATOR2__H__

#include "Element\GameObject\DynamicObject.h"
#include "DynamicObjectID.h"

class DynamicObj_BattleSimulator2 : public DynamicObj
{
public:
#pragma region ������ �� �Ҹ���
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