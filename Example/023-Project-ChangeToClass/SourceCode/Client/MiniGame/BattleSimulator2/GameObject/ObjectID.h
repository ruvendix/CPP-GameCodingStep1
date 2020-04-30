// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ��Ʋ �ùķ�����2���� ���Ǵ� ������Ʈ ID �����Դϴ�.
// ���� ������Ʈ�� ���� ������Ʈ �� �� ���Ե˴ϴ�.
// =====================================================================================

#ifndef OBJECT_ID_H__
#define OBJECT_ID_H__

#include "Common\CommonType.h"

enum class EObjID : Int32
{
	UNKNOWN = 0,

	START_STATIC_OBJ_ID,
	WALL,
	END_STATIC_OBJ_ID,

	START_DYNAMIC_OBJ_ID,
	VIKING,
	MEDIEVAL_KNIGHT,
	END_DYNAMIC_OBJ_ID,
};

#endif