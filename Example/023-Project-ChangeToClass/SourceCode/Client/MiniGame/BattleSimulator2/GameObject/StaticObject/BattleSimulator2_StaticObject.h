// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2���� ���Ǵ� �⺻ ���� ������Ʈ�Դϴ�.
// =====================================================================================

#ifndef BATTLE_SIMULATOR2_STATIC_OBJ__H__
#define BATTLE_SIMULATOR2_STATIC_OBJ__H__

#include "Element\GameObject\StaticObject.h"
#include "StaticObjectID.h"

class BattleSimulator2_StaticObj : public StaticObj
{
public:
#pragma region ������ �� �Ҹ���
	using StaticObj::StaticObj;

	BattleSimulator2_StaticObj() = default;
	virtual ~BattleSimulator2_StaticObj() = default;

	BattleSimulator2_StaticObj(EStaticObjID objID);
#pragma endregion

	virtual EErrorType OnPreSaveFile(FILE* pFileStream) override;

	EStaticObjID getObjID() const
	{
		return m_objID;
	}

private:
	EStaticObjID m_objID = EStaticObjID::UNKNOWN;
};

#endif