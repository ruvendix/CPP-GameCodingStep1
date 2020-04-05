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

#include "StaticObject_BattleSimulator2.h"

class Wall : public StaticObj_BattleSimulator2
{
public:
#pragma region ������ �� �Ҹ���
	using StaticObj_BattleSimulator2::StaticObj_BattleSimulator2;
	virtual ~Wall() = default;
#pragma endregion

	virtual EErrorType OnRender() override;
};

#endif