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

enum class EStaticObjID : Int32
{
	UNKNOWN = 0,
	WALL,
	END, // ���� ������Ʈ ID���� �������� ���!
};

enum class EDynamicObjID : Int32
{
	UNKNOWN = static_cast<Int32>(EStaticObjID::END),
	VIKING,
	MEDIEVAL_KNIGHT
};

#endif