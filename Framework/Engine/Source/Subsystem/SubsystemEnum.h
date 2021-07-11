// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ����ý��ۿ� ���Ǵ� �������Դϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonType.h"

enum class ESubsystemType : Int32
{
	UNKNOWN = -1,

	CONSOLE_HANDLER,
	TIME_HANDLER,
	FILE_HANDLER,

	GAME_OBJECT_MANAGER,
	FRAME_MANAGER,
	PATH_MANAGER,
	ACTOR_MANAGER,

	COUNT,
};