// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2�� ���忡 ���Ǵ� ���Դϴ�.
// =====================================================================================

#ifndef WALL__H__
#define WALL__H__

#include "Element\GameObject\StaticObject.h"
#include "..\ObjectID.h"

class Wall final : public StaticObj
{
	DECLARE_RTTI(Wall, StaticObj);

public:
#pragma region ������ �� �Ҹ���
	using StaticObj::StaticObj;
	virtual ~Wall() = default;
#pragma endregion
};

#endif