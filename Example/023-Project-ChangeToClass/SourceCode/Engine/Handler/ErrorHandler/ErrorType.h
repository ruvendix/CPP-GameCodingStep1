// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���� ���� �����Դϴ�.
// ���ο� ������ ���⿡ �߰��ؾ� �մϴ�.
// =====================================================================================

#ifndef ERROR_TYPE__H__
#define ERROR_TYPE__H__

#include "Common\CommonType.h"

enum class EErrorType : Int32
{
	NONE = 0,
	INIT_FAILED,
	UPDATE_FAILED,
	RENDER_FAILED,
	FINAL_FAILED,
};

#endif