// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2���� ���Ǵ� �⺻ ���� ������Ʈ�Դϴ�.
// =====================================================================================

#ifndef BATTLE_SIMULATOR2_DYNAMIC_OBJ__H__
#define BATTLE_SIMULATOR2_DYNAMIC_OBJ__H__

#include "Element\GameObject\DynamicObject.h"
#include "DynamicObjectID.h"

class BattleSimulator2_DynamicObj : public DynamicObj
{
public:
#pragma region ������ �� �Ҹ���
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