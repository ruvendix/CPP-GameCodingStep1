// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 서브시스템의 인터페이스입니다.
// =====================================================================================
#pragma once

#include "Common/CommonMacro.h"
#include "Subsystem/SubsystemEnum.h"
#include "Subsystem/SubsystemMacro.h"

// 전방 선언
class ParentSubsystemData;

class ISubsystem
{
public:
	ISubsystem() = default;
	virtual ~ISubsystem() = default;

	virtual void SetUp() PURE_FUNC;
	virtual void CleanUp() PURE_FUNC;
};