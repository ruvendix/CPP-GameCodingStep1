// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� ���� ������Ʈ�� ����Դϴ�.
// =====================================================================================

#ifndef DYNAMIC_OBJ__H__
#define DYNAMIC_OBJ__H__

#include "GameObject.h"

enum class EPreferMoveAxis : Int32
{
	UNKNOWN,
	X,
	Y,
};

class DynamicObj : public GameObj
{
	DECLARE_RTTI(DynamicObj, GameObj);

public:
#pragma region ������ �� �Ҹ���
	using GameObj::GameObj;
	virtual ~DynamicObj() = default;
#pragma endregion

	bool MoveToTarget(std::shared_ptr<DynamicObj> spTargetObj);

	virtual EGameObjType OnGetType() const override
	{
		return EGameObjType::DYNAMIC;
	}

	void setMoveSpeed(Real32 moveSpeed)
	{
		m_moveSpeed = moveSpeed;
	}

	void setPreferMoveAxis(EPreferMoveAxis axis)
	{
		m_preferMoveAxis = axis;
	}

private:
	Real32 m_moveSpeed = 0.0f;
	Real32 m_accumulationMove = 0.0f;
	EPreferMoveAxis m_preferMoveAxis = EPreferMoveAxis::UNKNOWN;
};

#endif