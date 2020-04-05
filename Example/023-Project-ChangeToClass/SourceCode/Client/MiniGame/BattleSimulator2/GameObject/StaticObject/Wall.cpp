// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ������� ���忡 ���Ǵ� ���Դϴ�.
// =====================================================================================

#include "PCH.h"
#include "Wall.h"

#include "Controller\ConsoleController.h"

EErrorType Wall::OnRender()
{
	const COORD& pos = getPos();
	PUT_STRING(pos.X * getShape().size(), pos.Y, getShape().c_str());
	return EErrorType::NONE;
}
