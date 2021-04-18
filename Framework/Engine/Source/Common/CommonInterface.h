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

class IService
{
public:
	IService() = default;
	virtual ~IService() = default;

	virtual EReturnType SetUp() = 0;
	virtual EReturnType CleanUp() = 0;
};

class IGameObject
{
public:
	IGameObject() = default;
	virtual ~IGameObject() = default;

	virtual EReturnType SetUp() = 0;
	virtual EReturnType CleanUp() = 0;

	virtual EReturnType Update() = 0;
	virtual EReturnType Render() = 0;
};