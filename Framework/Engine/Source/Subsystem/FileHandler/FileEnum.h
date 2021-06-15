// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� �ڵ鷯�� ���Ǵ� �������Դϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonType.h"

enum class EFileMode : Int32
{
	UNKNOWN = -1,
	TEXT,
	BINARY,
	COUNT,
};

enum class EAccessMode : Int32
{
	UNKNOWN = -1,
	READ,
	WRITE,
	APPEND,
	READ_PLUS,
	WRITE_PLUS,
	APPEND_PLUS,
	COUNT,
};