// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ����� ���� ������ Ÿ�� �������Դϴ�.
// ������ Ÿ�� �����ڰ� �ʱ�ȭ���� �ʾ��� �� ���˴ϴ�.
// FIND_SUBSYSTEM() ��ũ�θ� ���ؼ��� ���˴ϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonBase.h"
#include "IFrameManager.h"

class IFrameManagerNull : public IFrameManager
{
public:
	virtual void SetUp() OVERRIDE_EMPTY_FUNC;
	virtual void CleanUp() OVERRIDE_EMPTY_FUNC;

	virtual void UpdateFrameTime() OVERRIDE_EMPTY_FUNC;
};