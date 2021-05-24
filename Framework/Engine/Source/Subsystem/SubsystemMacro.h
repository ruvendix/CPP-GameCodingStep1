// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ����ý����� �ʿ��� ��ũ�� �Լ� �����Դϴ�.
// =====================================================================================
#pragma once

#define GENERATE_MATCH_TYPE(subsystemType)\
public:\
	static constexpr ESubsystemType MatchType()\
	{\
		return subsystemType;\
	}

#define FIND_SUBSYSTEM(TSubsystem) SubsystemLocator::I().FindSubsystem<TSubsystem>()