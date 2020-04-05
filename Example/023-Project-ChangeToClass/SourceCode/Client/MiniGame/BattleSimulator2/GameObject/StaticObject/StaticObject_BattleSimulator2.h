// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2���� ���Ǵ� �⺻ ���� ������Ʈ�Դϴ�.
// =====================================================================================

#ifndef STATIC_OBJ_BATTLE_SIMULATOR2__H__
#define STATIC_OBJ_BATTLE_SIMULATOR2__H__

#include "Element\GameObject\StaticObject.h"
#include "StaticObjectID.h"

class StaticObj_BattleSimulator2 : public StaticObj
{
public:
#pragma region ������ �� �Ҹ���
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