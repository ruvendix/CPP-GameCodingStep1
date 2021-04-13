// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ���������� ���Ǵ� �������̽� �����Դϴ�.
// =====================================================================================
#pragma once

#include "CommonMacro.h"
#include "CommonEnum.h"

class IDefault
{
public:
	IDefault() = default;
	virtual ~IDefault() = default;

	virtual EReturnType SetUp() PURE_FUNC
	virtual EReturnType CleanUp() PURE_FUNC
};