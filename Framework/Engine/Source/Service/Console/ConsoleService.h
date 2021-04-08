// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 콘솔 서비스입니다.
// 콘솔창을 다룰 때 사용됩니다.
// =====================================================================================
#pragma once

#include "Common/Common.h"
#include "IConsoleService.h"

class ConsoleService final : public IConsoleService
{
public:
	ConsoleService() = default;
	virtual ~ConsoleService() = default;

	virtual void TestFunc() override
	{
		printf("서비스 로케이터로 콘솔 서비스의 함수 호출!\n");
	}
};

class ConsoleService_Version2 final : public IConsoleService
{
public:
	ConsoleService_Version2() = default;
	virtual ~ConsoleService_Version2() = default;

	virtual void TestFunc() override
	{
		printf("서비스 로케이터로 콘솔 서비스 버전2의 함수 호출!\n");
	}
};