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

class IGameObject
{
public:
	IGameObject() = default;
	virtual ~IGameObject() = default;

	virtual void SetUp() PURE_FUNC;
	virtual void CleanUp() PURE_FUNC;

	virtual void Update() PURE_FUNC;
	virtual void Render() PURE_FUNC;
};