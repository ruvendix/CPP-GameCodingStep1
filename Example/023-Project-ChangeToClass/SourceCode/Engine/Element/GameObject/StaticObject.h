// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��� ���� ������Ʈ�� ����Դϴ�.
// =====================================================================================

#ifndef STATIC_OBJ__H__
#define STATIC_OBJ__H__

#include "GameObject.h"

class StaticObj : public GameObj
{
public:
#pragma region ������ �� �Ҹ���
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