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
	OUT_OF_HEAP_MEMORY,

	DUPLICATED_SUBSYSTEM,
	REGISTER_SUBSYSTEM_FAIL,
	NOT_EXIST_SUBSYSTEM,

	INVALID_SCREEN_COLOR,
	CLEAR_SCREEN_FAIL,

	OPEN_FILE_STREAM_FAIL,
	CLOSE_FILE_STREAM_FAIL,

	DUPLICATED_COMPONENT,
	ADD_COMPONENT_FAIL,
	NOT_EXIST_COMPONENT,

	OUT_OF_GAMEOBJECT,

	CASTING_FAIL,
	COUNT,
};