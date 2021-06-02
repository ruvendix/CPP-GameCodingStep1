// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ����ý����� �������̽��Դϴ�.
// =====================================================================================
#pragma once

class ISubsystem
{
	friend class SubsystemLocator;

public:
	ISubsystem() = default;
	virtual ~ISubsystem() = default;

	virtual void SetUp() = 0;
	virtual void CleanUp() = 0;
};