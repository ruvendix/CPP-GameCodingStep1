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

enum class EErrorCode : Int32
{
	UNKNOWN = -1,
	INDIRECT_NULLPTR,
	OUT_OF_GAMEOBJECT,
	INVALID_SCREEN_COLOR,
	CLEAR_SCREEN_FAIL,
	OPEN_FILE_STREAM_FAIL,
	CLOSE_FILE_STREAM_FAIL,
	COUNT,
};