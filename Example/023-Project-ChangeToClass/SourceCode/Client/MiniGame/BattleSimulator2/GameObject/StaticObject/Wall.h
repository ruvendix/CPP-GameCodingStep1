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

#include "BattleSimulator2_StaticObject.h"

class Wall : public BattleSimulator2_StaticObj
{
public:
#pragma region ������ �� �Ҹ���
	using BattleSimulator2_StaticObj::BattleSimulator2_StaticObj;
	virtual ~Wall() = default;
#pragma endregion
};

#endif