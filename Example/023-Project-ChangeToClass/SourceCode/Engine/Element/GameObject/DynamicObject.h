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

class DynamicObj : public GameObj
{
public:
#pragma region ������ �� �Ҹ���
	using GameObj::GameObj;
	virtual ~DynamicObj() = default;
#pragma endregion

	virtual EGameObjType getType() const override
	{
		return EGameObjType::DYNAMIC;
	}

private:
	
};

#endif