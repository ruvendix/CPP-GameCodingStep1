// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// Ÿ�� �ڵ鷯�Դϴ�.
// �ð� ��ȯ �� �ð� ���� ������ �ٷ�ϴ�.
// =====================================================================================
#pragma once

#include "ITimeHandler.h"

class TimeHandler : public ITimeHandler
{
	ONLY_SUBSYSTEM(TimeHandler);

	virtual void SetUp() override;
	virtual void CleanUp() override;
};