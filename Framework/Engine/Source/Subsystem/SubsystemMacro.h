// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ����ý����� �ʿ��� ��ũ�� �Լ� �����Դϴ�.
// =====================================================================================
#pragma once

#define GENERATE_SUBSYSTEM_ID(eID)\
public:\
	static constexpr ESubsystemID ID()\
	{\
		return eID;\
	}

#define ONLY_SUBSYSTEM(SubsystemType)\
private:\
	friend class SubsystemLocator;\
	SubsystemType() = default;\
	virtual ~SubsystemType() = default;

#define ONLY_SUBSYSTEM_CTOR(SubsystemType)\
private:\
	friend class SubsystemLocator;\
	SubsystemType();\
	virtual ~SubsystemType() = default;

#define FIND_SUBSYSTEM(SubsystemType) SubsystemLocator::I().FindSubsystem<SubsystemType>()