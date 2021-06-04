// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 서브시스템이 필요한 매크로 함수 모음입니다.
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