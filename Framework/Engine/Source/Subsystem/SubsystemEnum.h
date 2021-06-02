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

enum class ESubsystemID : Int32
{
	UNKNOWN = -1,
	LOGGER,
	ERROR_HANLDER,
	CONSOLE_HANDLER,
	GAME_OBJECT_MANAGER,
	FRAME_TIME_MANAGER,
	COUNT,
};