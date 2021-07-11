// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ����ý����� �������̽��Դϴ�.
// =====================================================================================
#pragma once

#include "Common/CommonMacro.h"
#include "Subsystem/SubsystemEnum.h"
#include "Subsystem/SubsystemMacro.h"

class ISubsystem : public ICommon
{
public:
	ISubsystem() = default;
	virtual ~ISubsystem() = default;
};