// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ������� ���忡 ���Ǵ� ���Դϴ�.
// =====================================================================================

#ifndef SIDE_WALL__H__
#define SIDE_WALL__H__

#include "Element\GameObject\StaticObject.h"

class Wall : public StaticObj
{
public:
#pragma region ������ �� �Ҹ���
	using StaticObj::StaticObj;
	virtual ~Wall() = default;
#pragma endregion

	virtual EErrorType OnRender() override;
};

#endif