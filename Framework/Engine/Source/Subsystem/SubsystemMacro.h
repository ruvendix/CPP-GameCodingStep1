// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// �� ���۹��� ũ������Ƽ�� Ŀ���� ������ǥ�� 4.0 ���� ���̼����� ���� �̿��� �� �ֽ��ϴ�.
// http://creativecommons.org/licenses/by/4.0/
//
// ����ý����� �ʿ��� ��ũ�� �Լ� �����Դϴ�.
// =====================================================================================
#pragma once

#define GENERATE_SUBSYSTEM_TYPE(value)\
public:\
	static constexpr ESubsystemType Type()\
	{\
		return value;\
	}

#define GENERATE_SUBSYSTEM_DATA(ChildSubsystemData)\
public:\
	using DataPtr = std::shared_ptr<ChildSubsystemData>;\
	DataPtr Data()\
	{\
		if (m_spData == nullptr)\
		{\
			m_spData = std::make_shared<ChildSubsystemData>();\
		}\
		return DownCastSmartPointer<SubsystemData, ChildSubsystemData>(m_spData);\
	}\
private:\
	DataPtr m_spData = nullptr;

#define ONLY_SUBSYSTEM(SubsystemType)\
private:\
	FRIEND_CLASS(SubsystemLocator);\
	SubsystemType() = default;\
	virtual ~SubsystemType() = default;

#define ONLY_SUBSYSTEM_CTOR(SubsystemType)\
private:\
	FRIEND_CLASS(SubsystemLocator);\
	SubsystemType();\
	virtual ~SubsystemType() = default;

#define FIND_SUBSYSTEM(SubsystemType) SubsystemLocator::I().FindSubsystem<SubsystemType>()