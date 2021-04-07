// =====================================================================================
// Copyright(c) 2020, Ruvendix. All Rights Reserved.
// 
// 이 저작물은 크리에이티브 커먼즈 저작자표시 4.0 국제 라이선스에 따라 이용할 수 있습니다.
// http://creativecommons.org/licenses/by/4.0/
//
// 콘솔창을 다루는 핸들러입니다.
// =====================================================================================
#pragma once

#include "Common/Common.h"

class ConsoleHandler final
{
	DECLARE_LOCAL_SINGLETON(ConsoleHandler);

public:
	void TestFunc()
	{
		printf("싱글톤으로 함수 호출!\n");
	}
};